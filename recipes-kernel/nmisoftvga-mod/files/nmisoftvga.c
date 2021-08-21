#include <linux/errno.h>
#include <linux/fb.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/spi/spi.h>

static unsigned max_transfer_size = 4096;
module_param(max_transfer_size, uint, S_IRUGO);
MODULE_PARM_DESC(max_transfer_size, "Maximum transfer size");

struct device_data {
	struct spi_device *device;
	u8 *tx_buffer;
	u8 *rx_buffer;
};

static void fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
}

static void copyarea(struct fb_info *info, const struct fb_copyarea *region)
{
}

static void imageblit(struct fb_info *info, const struct fb_image *image)
{
}

static const struct fb_ops ops = {
	.owner		= THIS_MODULE,
	.fb_fillrect 	= fillrect,
	.fb_copyarea	= copyarea,
	.fb_imageblit	= imageblit,
};

static int probe(struct spi_device *dev)
{
	struct device_data *data;
	struct fb_info *info;
	int status = 0;

	info = framebuffer_alloc(sizeof(struct device_data), &dev->dev);
	if (!info) {
		status = -ENOMEM;
		goto exit;
	}

	info->fbops = &ops;

	data = info->par;
	data->device = dev;

	data->tx_buffer = kzalloc(max_transfer_size, GFP_KERNEL);
	if (!data->tx_buffer) {
		status = -ENOMEM;
		goto err_fb_alloc;
	}

	data->rx_buffer = kzalloc(max_transfer_size, GFP_KERNEL);
	if (!data->rx_buffer) {
		status = -ENOMEM;
		goto err_tx_buf_alloc;
	}

	spi_set_drvdata(dev, info);

	if (register_framebuffer(info) < 0) {
		status = -EINVAL;
		goto err_rx_buf_alloc;
	}

	return 0;

err_rx_buf_alloc:
	kfree(data->rx_buffer);
err_tx_buf_alloc:
	kfree(data->tx_buffer);
err_fb_alloc:
	framebuffer_release(info);
exit:
	return status;
}

static int remove(struct spi_device *dev)
{
	struct fb_info *info = spi_get_drvdata(dev);
	struct device_data *data;

	if (info) {
		unregister_framebuffer(info);

		data = info->par;

		if (data->tx_buffer)
			kfree(data->tx_buffer);

		if (data->rx_buffer)
			kfree(data->rx_buffer);
	}

	framebuffer_release(info);

	return 0;
}

static const struct spi_device_id id_table[] = {
	{ "nmisoftvga" },
	{ }
};
MODULE_DEVICE_TABLE(spi, id_table);

#if defined(CONFIG_OF)
static const struct of_device_id of_match_table[] = {
	{ .compatible = "nmisoft,vga", },
	{ }
};
MODULE_DEVICE_TABLE(of, of_match_table);
#endif

static struct spi_driver nmisoftvga_driver = {
	.driver = {
		.name = "nmisoftvga",
		.of_match_table = of_match_ptr(of_match_table),
	},
	.probe = probe,
	.remove = remove,
	.id_table = id_table,
};
module_spi_driver(nmisoftvga_driver);

MODULE_LICENSE("GPL");

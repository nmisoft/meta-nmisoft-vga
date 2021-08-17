#include <linux/module.h>
#include <linux/of.h>
#include <linux/spi/spi.h>

static int probe(struct spi_device *dev)
{
	return 0;
}

static int remove(struct spi_device *dev)
{
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

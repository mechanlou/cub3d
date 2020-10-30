#include "cub.h"

static void	init_bmp_data(t_params params, t_bmp *bmp)
{
	ft_bzero(bmp->header, 54);
	bmp->width = params.window_xy[0];
	bmp->height = params.window_xy[1];
	bmp->bytes_count = 32;
	bmp->width_in_bytes = ((bmp->width *
		bmp->bytes_count + 31) / 32) * 4;
	bmp->image_size = bmp->width_in_bytes * bmp->height;
	bmp->bytes_size = 40;
	bmp->bfoffbits = 54;
	bmp->file_size = 54 + bmp->image_size;
	bmp->biplanes = 1;
}

static void	fill_header(t_bmp *bmp)
{
	ft_memcpy(bmp->header, "BM", 2);
	ft_memcpy(bmp->header + 2, &bmp->file_size, 4);
	ft_memcpy(bmp->header + 10, &bmp->bfoffbits, 4);
	ft_memcpy(bmp->header + 14, &bmp->bytes_size, 4);
	ft_memcpy(bmp->header + 18, &bmp->width, 4);
	ft_memcpy(bmp->header + 22, &bmp->height, 4);
	ft_memcpy(bmp->header + 26, &bmp->biplanes, 4);
	ft_memcpy(bmp->header + 28, &bmp->bytes_count, 4);
	ft_memcpy(bmp->header + 34, &bmp->image_size, 4);
	bmp->fd = open("./capture.bmp", O_TRUNC | O_WRONLY | O_CREAT, 0777);
}

void		cub_save_bmp(t_params params, t_image image)
{
	int		height_to_write;
	t_bmp	bmp;

	init_bmp_data(params, &bmp);
	fill_header(&bmp);
	height_to_write = bmp.height;
	write(bmp.fd, bmp.header, 54);
	while (height_to_write)
	{
		write(bmp.fd, image.data
		+ (height_to_write * bmp.width * 4), bmp.width * 4);
		height_to_write--;
	}
	close(bmp.fd);
}
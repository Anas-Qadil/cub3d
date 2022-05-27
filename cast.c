/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 09:32:08 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/26 09:36:21 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void    cast(t_data *mlx, float rayAngle)
{
	int color = 0x00e83838;
	int max_ray_checks = 8;
	int r = 0, mx, my, mp, dof;
	float disT;
	float rx, ry, ra, xo, yo, disV, disH, vx, vy;
	ra=FixAng(pa+30);
	int i = 0;
	float hx = px, hy = py;
	while (r < 60)
	{
		disV = 1000000;
		float Tan=tan(degToRad(ra));
		dof = 0;
		if(cos(degToRad(ra)) > 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
		else if(cos(degToRad(ra)) < -0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
		else { rx=px; ry=py; dof=8;}
		
		while (dof < max_ray_checks)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[my][mx] == 1)
			{
				disV = cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);
				dof = max_ray_checks;
			}
			else 
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		vx = rx; vy = ry;
		
		dof = 0; disH = 100000;
		Tan=1.0/Tan;
		if (sin(degToRad(ra))> 0.001) 
		{
			ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;
		}
		else if (sin(degToRad(ra))<-0.001) {
			ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;
		}
		else
		{
			rx = px;
			ry = py;
			dof = max_ray_checks;
		}
		while (dof < max_ray_checks)
		{
			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx; 
			if (mp > 0 && mp < mapX * mapY && map[my][mx] == 1)
			{
				dof = max_ray_checks;
				disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		float shade = 1;
		if (disV < disH)
		{
			shade = 0.5;
			rx = vx;
			ry = vy;
			disH = disV;
		}
		
		draw_line(px, py, rx, ry, mlx, color); // hna l cast d ray 
		
  		int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));
		int lineH = (mapS*320)/(disH); 
		float ty_step=64.0/(float)lineH; 
		float ty_off=0; 
		if(lineH>320){ ty_off=(lineH-320)/2.0; lineH=320;}  //line height and limit
		int lineOff = 160 - (lineH>>1);
		
		int y = 0;
		float ty = ty_off * ty_step;
		
		float tx;
		if(shade==1){ tx=(int)(rx/2.0)%64; if(ra>180){ tx=63-tx;}}  
  		else        { tx=(int)(ry/2.0)%64; if(ra>90 && ra<270){ tx=63-tx;}}
		  
		while (y < lineH)
		{
			int j = 0;
			while (j < 8)
			{
			int c = mlx->buff[((int)(ty) * 64) + (int)(tx)];
			int color = c;
				my_mlx_pixel_put(mlx, r * 8 - j + 1200, y + lineOff, color);
				j++;
			}
			y++;
			ty += ty_step;
			
		}



		//draw floors
		int y123 = lineOff + lineH;
		while (y123 < 320)
		{
			draw_floors(r, y123, mlx);
			draw_ceiling(r, 320 - y123, mlx);
			y123++;
		}
		
		ra=FixAng(ra-1);  
		r++;
	}
}

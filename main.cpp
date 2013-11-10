#include <stdio.h>
#include <allegro.h>
#include "teclado.h"

volatile int exit_program = FALSE;

void fechar_programa()
{
 	 exit_program = TRUE;
}
END_OF_FUNCTION(fechar_programa)

void init();
void deinit();

int main() {
	init();
	
	int coordenada_x = 110;
	float teta = 90;
	int i, j;
	int sel_i = 0, sel_j = 0;
	
	LOCK_VARIABLE(exit_program);
	LOCK_FUNCTION(fechar_programa);
	set_close_button_callback(fechar_programa);
	
	//BITMAPS
	BITMAP* buffer   = create_bitmap(SCREEN_W, SCREEN_H);
	BITMAP* boneco   = load_bitmap("imagens/boneco.bmp", NULL);
	BITMAP* sky      = load_bitmap("imagens/ceu.bmp" , NULL);
	BITMAP* montanha = load_bitmap("imagens/montanha.bmp" , NULL);
	
	 
	while ( ! exit_program) 
	{
	 	  //INPUT
	 	  keyboard_input();
	 	  
		  if(key[KEY_ESC]){ fechar_programa(); }	

		  if(apertou(KEY_UP))
			   sel_i--;
		  else if(apertou(KEY_DOWN))
		  	   sel_i++;  
		  else if(apertou(KEY_LEFT))
		  	   sel_j--;
		  else if(apertou(KEY_RIGHT))
		  	   sel_j++;		  
		   	  
	 	  //UPDATE
	 	  coordenada_x++;
	 	  teta += 0.1;
	 	  
	 	  if(sel_i > 9)
	           sel_i = 0;
		  else if(sel_i < 0)
		  	   sel_i = 9;
		  else if(sel_j > 7)
		  	   sel_j = 0;
		  else if(sel_j < 0)
	 	  	   sel_j = 7;
	 	  
	 	  //DRAW
	 	  //screen é um ponteiro para o bitmap da imagem
    	  //circlefill(buffer, coordenada_x, 110, 50, makecol(255, 0, 0));
    	  //draw_sprite(screen, buffer, 0, 0);
    	  
    	  /**
    	  set_burn_blender(255, 255, 255, 128);
    	  
    	  draw_sprite(buffer, sky, 0, 0);
    	  draw_sprite(buffer, montanha, 0, 0);
		  draw_sprite(buffer, boneco, 200, 38);    	
		  rotate_sprite(buffer, boneco, 200, 380, ftofix(teta));  
		  */
		  
		  for(i = 0; i < 10; i++)
		  {
		   	   for(j = 0; j < 8; j++)
		   	   {
			   		rect(buffer, 
					   50 + j * 40, 
 				   	   50 + i * 40,
					   50 + j * 40 + 40,
					   50 + i * 40 + 40,
					   makecol(255, 255, 255) 
			       );
   	           } 
	      }
    	  
    	  rectfill(
		  		   buffer, 
				   50 + sel_j * 40, 
				   50 + sel_i * 40, 
				   50 + sel_j * 40 + 40,
				   50 + sel_i * 40 + 40,
				   makecol(255, 0, 0)
	      );
    	  
    	  draw_sprite(screen, buffer, 0, 0);
		  clear(buffer);
    }
	
	//FINALIZAÇÃO
	destroy_bitmap(buffer);
	destroy_bitmap(boneco);
	destroy_bitmap(sky);
	destroy_bitmap(montanha);
	
	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
	
	set_window_title("Campo minado");
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

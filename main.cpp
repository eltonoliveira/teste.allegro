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
	BITMAP* cursor   = load_bitmap("imagens/cursor.bmp", NULL);
	
	//VARIAVEIS
	int estado_anterior_SPACE;
	//SONS
	SAMPLE* efeito 	= load_sample("sons/efeito.wav");
	MIDI* musica 	= load_midi("sons/musica.mid");
	
	play_midi(musica, TRUE);

	while ( ! exit_program) 
	{
	 	  //INPUT
	 	  keyboard_input();
	 	  
		  estado_anterior_SPACE = key[KEY_SPACE];
	 	  poll_keyboard();
	 	  
		  if(key[KEY_ESC]){ fechar_programa(); }	

		  if(estado_anterior_SPACE == 0 && key[KEY_SPACE] != 0){ play_sample(efeito, 255, 128, 1000, FALSE); }
		  
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
		  rectfill(buffer, 100, 100, 200, 200, makecol(0, 0, 255)); 
		  
		  if(mouse_x > 100 && mouse_x < 200 &&
			 mouse_y > 100 && mouse_y < 200
		  )
		  {
		   	 rectfill(buffer, 100, 100, 200, 200, makecol(255, 0, 0)); 
		   	 
		   	 if(mouse_b == 1)
		   	 {
 			    //mouse_b = 0;
 			    textout_ex(buffer, font, "Pressionou botao esquerdo", 130, 350, makecol(255, 255, 255), -1);  		
			 }
		  }
		  
		  textout_ex(buffer, font, "Jogar", 130, 150, makecol(255, 255, 255), -1);  
		  
		   	  
    	  draw_sprite(buffer, cursor, mouse_x - 6, mouse_y);
    	  draw_sprite(screen, buffer, 0, 0);
		  clear(buffer);
    }
	
	//FINALIZAÇÃO
	destroy_bitmap(buffer);
	destroy_bitmap(boneco);
	destroy_bitmap(sky);
	destroy_bitmap(montanha);
	destroy_bitmap(cursor);
	destroy_sample(efeito);
	destroy_midi(musica);
	stop_midi();
	
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
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	
	
	set_window_title("Campo minado");
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

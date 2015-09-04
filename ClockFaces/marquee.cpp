#ifdef FACE_MARQUEE

void marquee();
void scrollBigMessage(char *m);
void scrollMessage(char* top, char* bottom ,uint8_t top_font_size,uint8_t bottom_font_size, uint16_t top_color, uint16_t bottom_color);

void marquee() {
	char topLine[40] = {""};
	char botmLine[40] = "BOTTOM LINE GOES HERE";
	String tFull;

	//for (int show = 0; show < SHOWCLOCK ; show++) {
	int showTime = Time.now();

	while((Time.now() - showTime) < showClock) {
		if (mode_changed == 1)
			return;
		if(mode_quick){
			mode_quick = false;
			display_date();

#ifdef FACE_WEATHER
			quickWeather();
#endif
			marquee();
			return;
		}

		tFull = Time.timeStr();
		tFull.toUpperCase();
		tFull.toCharArray(topLine, tFull.length()+1);
		tFull = "";

		//scrollBigMessage(topLine);
		scrollMessage(topLine, botmLine, 53, 53, Green, Navy);

		delay(50);

		bgProcess();
	}
}


void scrollBigMessage(char *m) {
	matrix.setTextSize(1);
	int l = (strlen(m)*-6) - 32;
	for(int i = 32; i > l; i--){
		cls();
		matrix.setCursor(i,1);
		matrix.setTextColor(matrix.Color444(1,1,1));
		matrix.print(m);
		matrix.swapBuffers(false);
		delay(50);
		bgProcess();
	}

}

void scrollMessage(char* top, char* bottom ,uint8_t top_font_size,uint8_t bottom_font_size, uint16_t top_color, uint16_t bottom_color) {

	int l = ((strlen(top)>strlen(bottom)?strlen(top):strlen(bottom))*-5) - 32;

	for(int i=32; i > l; i--){

		if (mode_changed == 1 || mode_quick)
			return;

		cls();

		drawString(i,1,top,top_font_size, top_color);
		drawString(i,9,bottom, bottom_font_size, bottom_color);
		matrix.swapBuffers(false);
		delay(50);
		bgProcess();
	}

}
#endif
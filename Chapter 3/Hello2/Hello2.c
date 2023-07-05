#define kBaseResId		128
#define kMoveToFront	(WindowPtr)-1L

#define kHorizontalPixel 30
#define kVerticalPixel	50

void ToolBoxInit(void);
void WindowInit(void);

void main(void){
	ToolBoxInit();
	WindowInit();
	while(!Button());
} 

void ToolBoxInit(void){
	InitGraf(&thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(nil);
	InitCursor();
}

void WindowInit(void){
	WindowPtr window;
	window = GetNewWindow(kBaseResId, nil, kMoveToFront);
	if(window == nil){
		SysBeep(10);
		ExitToShell();
	}
	ShowWindow(window);
	SetPort(window);
	MoveTo(kHorizontalPixel, kVerticalPixel);
	DrawString("\pHello World");
}
	
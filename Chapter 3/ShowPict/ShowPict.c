#define kBaseResId		128
#define kMoveToFront	(WindowPtr)-1L


void ToolBoxInit(void);
void WindowInit(void);
void MainLoop(void);
void DrawMyPicture(void);
void CenterPict(PicHandle picture, Rect *destRectPtr);

void main(void){
	ToolBoxInit();
	WindowInit();
	
	DrawMyPicture();
	
	MainLoop();
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
}

void MainLoop(void){
	
	while(!Button()){
		// pass
	}
}

void DrawMyPicture(void){
	Rect pictureRect;
	WindowPtr window;
	PicHandle picture;
	
	window = FrontWindow();
	pictureRect = window->portRect;
	picture = GetPicture(kBaseResId);
	if(picture == nil){
		SysBeep(10);
		ExitToShell();
	}
	CenterPict(picture, &pictureRect);
	DrawPicture(picture, &pictureRect);
}

void CenterPict(PicHandle picture, Rect *destRectPtr){
	Rect windRect, pictRect;
	
	windRect = *destRectPtr;
	pictRect = (**(picture)).picFrame;
	
	
	OffsetRect(&pictRect, windRect.left - pictRect.left, windRect.top - pictRect.top);
	OffsetRect(&pictRect, windRect.right - pictRect.right, windRect.bottom - pictRect.bottom);
	
	destRectPtr = &pictRect;
		
}


	
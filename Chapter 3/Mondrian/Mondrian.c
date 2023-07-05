#define kBaseResId		128
#define kMoveToFront	(WindowPtr)-1L

#define kRandomUpperLimit 32768


long gFillColor = blackColor;

void ToolBoxInit(void);
void WindowInit(void);
void MainLoop(void);
void DrawRandomRect(void);
void RandomRect(Rect *rectPtr);
short Randomize(short range);

void main(void){
	ToolBoxInit();
	WindowInit();
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
	GetDateTime( (unsigned long *) (&randSeed));
	
	while(!Button()){
		DrawRandomRect();
		
		if(gFillColor == blackColor){
			gFillColor = whiteColor;
		}else{
			gFillColor = blackColor;
		}
	}
}

void DrawRandomRect(void){
	Rect randomRect;
	
	RandomRect(&randomRect);
	ForeColor(gFillColor);
	PaintOval(&randomRect);
}

void RandomRect(Rect *rectPtr){
	WindowPtr window;
	short right;
	short left;
	short top;
	short bottom;
	window = FrontWindow();
	
	right = window->portRect.right;
	left = window->portRect.left;
	top = window->portRect.top;
	bottom = window->portRect.bottom;
	
	rectPtr->left = Randomize(right-left);
	rectPtr->right = Randomize(right-left);
	rectPtr->top = Randomize(bottom-top);
	rectPtr->bottom = Randomize(bottom-top);
		
}

short Randomize(short range){
	long randomNumber;
	randomNumber = Random();
	if(randomNumber < 0){
		randomNumber *= -1;
	}
	return (randomNumber * range) / kRandomUpperLimit;
}

	
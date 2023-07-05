#define kNumLines		50
#define kMoveToFront	(WindowPtr)-1L
#define kRandomUpperLimit	32768
#define kEmptyString	"\p"
#define kEmptyTitle		kEmptyString
#define kVisible		true
#define kNoGoAway		false
#define kNilRefCon		(long)nil

Rect	gLines[kNumLines];
short gDeltaTop=3, gDeltaBottom=3;
short gDeltaLeft=2, gDeltaRight=6;



void ToolBoxInit(void);
void WindowInit(void);
void LinesInit(void);
void MainLoop(void);
void RandomRect(Rect *rectPtr);
short Randomize(short range);
void RecalcLine(short i);
void DrawLine(short i);

void main(void){
	ToolBoxInit();
	WindowInit();
	LinesInit();
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
	Rect totalRect, mBarRect;
	RgnHandle mBarRgn;
	WindowPtr window;
	
	window = NewWindow(nil, &(screenBits.bounds), kEmptyTitle, kVisible, plainDBox, 
	kMoveToFront, kNoGoAway, kNilRefCon);
	
	SetPort(window);
	
	FillRect(&(window->portRect), black);
	PenMode(patXor);
}

void LinesInit(void){
	short i;
	HideCursor();
	GetDateTime((unsigned long*) (&randSeed));
	RandomRect(&(gLines[0]));
	DrawLine(0);
	for(i=1; i<kNumLines; i++){
		gLines[i]=gLines[i-1];
		RecalcLine(i);
		DrawLine(i);
	}
}

void MainLoop(void){
	
	short i;
	while(!Button()){
		DrawLine(kNumLines-1);
		for(i=kNumLines-1; i>0; i--){
			gLines[i]=gLines[i-1];
		}
		RecalcLine(0);
		DrawLine(0);
	}
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

void RecalcLine(short i){
	WindowPtr window;
	Rect *linePtr;
	Rect draw;
	window = FrontWindow();
	linePtr = &gLines[i];
	draw = window->portRect;
	
	linePtr->top += gDeltaTop;
	if((linePtr->top < draw.top) || (linePtr->top > draw.bottom)){
		gDeltaTop *= -1;
		gLines[i].top += 2*gDeltaTop;
	}
	linePtr->bottom += gDeltaBottom;
	if((linePtr->bottom < draw.top) || (linePtr->bottom > draw.bottom)){
		gDeltaBottom *=-1;
		gLines[i].bottom += 2*gDeltaBottom;
	}
	linePtr->left += gDeltaLeft;
	if((linePtr->left < draw.left) || (linePtr->left > draw.right)){
		gDeltaLeft *=-1;
		gLines[i].left += 2*gDeltaLeft;
	}
	linePtr->right += gDeltaRight;
	if((linePtr->right < draw.left) || (linePtr->right > draw.right)){
		gDeltaRight *=-1;
		gLines[i].right += 2*gDeltaRight;
	}
}


void DrawLine(short i){
	Rect line = gLines[i];
	MoveTo(line.left, line.top);
	LineTo(line.right, line.bottom);
}

	
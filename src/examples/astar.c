#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480

size_t cellw = 32;
size_t cellh = 32;

#define GRIDW (WIDTH/cellw)
#define GRIDH (HEIGHT/cellh)

const SGColor PathFillColor = {0.5, 0.5, 0.0, 0.25}; // yellow
const SGColor PathLineColor = {0.75, 0.75, 0.0, 1.0};
const SGColor ClearFillColor = {0.0, 0.25, 0.5, 0.75}; // blue
const SGColor ClearLineColor = {0.0, 0.5, 0.75, 1.0};
const SGColor WallFillColor = {0.5, 0.0, 0.0, 0.75}; // red
const SGColor WallLineColor = {0.75, 0.25, 0.0, 1.0};
const SGColor StartFillColor = {0.5, 0.25, 0.0, 0.75}; // orange
const SGColor StartLineColor = {0.75, 0.5, 0.0, 1.0};
const SGColor GoalFillColor = {0.0, 0.5, 0.25, 0.75}; // green
const SGColor GoalLineColor = {0.0, 0.75, 0.5, 1.0};

void drawGrid(SGNavGrid* grid, SGenum type, SGColor color, SGbool fill)
{
	size_t i, j;
	SGNavGridData* data;
	sgDrawColor4fv(&color.r);
	for(i = 0; i < grid->width; i++)
	{
		for(j = 0; j < grid->height; j++)
		{
			data = sgNavGridGetNode(grid, i, j)->data;
			if(data->type == type)
				sgDrawRectangleWH(i * cellw, j * cellh, cellw, cellh, fill);
		}
	}
}

void drawPath(SGList* path, SGColor color, SGbool lines, SGbool fill)
{
	if(!path)
		return;

	SGListNode* node;
	SGNavGridData* data;
	if(lines)
		sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_STRIP);
	sgDrawColor4fv(&color.r);
	for(node = path->first; node; node = node->next)
	{
		data = node->item;
		if(lines)
			sgDrawVertex2f(data->x * cellw + cellw/2, data->y * cellh + cellh/2);
		else
			sgDrawRectangleWH(data->x * cellw, data->y * cellh, cellw, cellh, fill);
	}
	if(lines)
		sgDrawEnd();
}

/*
 * Why is this not in SGNavGrid itself? because it is not needed (we might add it as a DBG function oneday, however...)
 */
void resetScore(SGNavGrid* grid)
{
	size_t i, j;
	for(i = 0; i < grid->width + 2; i++)
		for(j = 0; j < grid->height + 2; j++)
			grid->grid[i][j]->score.f = grid->grid[i][j]->score.g = grid->grid[i][j]->score.h = SG_INF;
}

void drawScore(SGNavGrid* grid, SGFont* font, SGchar score, SGColor color)
{
	if(!score)
		return;

	sgDrawColor4fv(&color.r);

	SGAStarNode* node;
	float nscore;
	size_t i, j;
	for(i = 0; i < grid->width; i++)
	{
		for(j = 0; j < grid->height; j++)
		{
			node = sgNavGridGetNode(grid, i, j);
			switch(score)
			{
				case 'F': nscore = node->score.f; break;
				case 'G': nscore = node->score.g; break;
				case 'H': nscore = node->score.h; break;
				default: nscore = SG_INF;
			}
			sgFontPrintCenteredf(font, i * cellw + cellw/2, j * cellh + cellh/2, "%.1f", nscore);
		}
	}
}

SGNavGrid* grid = NULL;
SGFont* score;
SGbool instructions = SG_FALSE;
SGbool slow = SG_FALSE;
SGchar scores = 0;
SGbool changed = SG_TRUE;
SGbool diag = SG_TRUE;
SGbool wdiag = SG_FALSE;

void recreateGrid(SGbool copy, SGbool refont)
{
	SGNavGrid* prev = grid;
	SGFont* prevfont = score;

	grid = sgNavGridCreate(GRIDW, GRIDH, diag, wdiag);

	size_t i, j;
	SGNavGridData* data;
	if(copy && prev)
	{
		for(i = 0; i < prev->width; i++)
		{
			for(j = 0; j < prev->height; j++)
			{
				data = sgNavGridGetData(prev, i, j);
				switch(data->type)
				{
					case SG_NAVGRID_CLEAR: break;
					case SG_NAVGRID_WALL: sgNavGridAddWall(grid, i, j); break;
					case SG_NAVGRID_START: sgNavGridAddStart(grid, i, j); break;
					case SG_NAVGRID_GOAL: sgNavGridAddGoal(grid, i, j); break;
				}
			}
		}
	}
	else
	{
		sgNavGridAddStart(grid, 1, 1);
		sgNavGridAddGoal(grid, GRIDW - 2, GRIDH - 2);
	}

	if(prev)
		sgNavGridDestroy(prev);

	if(refont)
	{
		score = sgFontResize(prevfont, cellw / 4.0);
		//if(score != prevfont)
			//sgFontDestroy(prevfont);
	}

	changed = SG_TRUE;
}

void SG_EXPORT evKeyboardKeyPress(SGEntity* entity, SGenum key)
{
	if(key == SG_KEYBOARD_KEY_F1)
	{
		instructions = !instructions;
	}
	else if(key == 'S')
	{
		slow = !slow;
		changed = SG_TRUE;
	}
	else if(key == 'F')
		scores = (scores != 'F') ? 'F' : 0;
	else if(key == 'G')
		scores = (scores != 'G') ? 'G' : 0;
	else if(key == 'H')
		scores = (scores != 'H') ? 'H' : 0;
	else if(key == '+' || key == SG_KEYBOARD_KEY_KP_ADD)
	{
		if(cellw < 128)
		{
			cellw <<= 1;
			cellh <<= 1;
			recreateGrid(SG_FALSE, SG_TRUE);
		}
	}
	else if(key == '-' || key == SG_KEYBOARD_KEY_KP_SUBTRACT)
	{
		if(cellw > 8)
		{
			cellw >>= 1;
			cellh >>= 1;
			recreateGrid(SG_FALSE, SG_TRUE);
		}
	}
	else if(key == 'D')
	{
		diag = !diag;
		recreateGrid(SG_TRUE, SG_FALSE);
	}
	else if(key == 'W')
	{
		wdiag = !wdiag;
		recreateGrid(SG_TRUE, SG_FALSE);
	}
}

void drawInstructions(SGFont* headf, SGFont* textf, SGColor fill, SGColor line, SGColor head, SGColor text)
{
	SGVec2 border = sgVec2f(WIDTH / 8, HEIGHT / 8);
	SGVec2 margin = sgVec2f(16, 24);
	SGVec2 csize;

	const char* headt = "Instructions:";
	const char* textt =
	"Editing the field:\n"
	"- Create walls: Left mouse button\n"
	"- Remove walls: Right mouse button\n"
	"- Set start: '1' key while holding mouse over desired location\n"
	"- Set goal: '2' key while holding mouse over desired location\n"
	"\n"
	"Controlling the grid:\n"
	"- Slow search: 'S' key\n"
	"- Score display: Keys 'F' (sum), 'G' (so far), 'H' (heuristic estimate)\n"
	"- Resize grid: Keys '+' and '-' (WARNING: will destroy current grid!)\n"
	"- Toggle diagonal traversal: 'D' key\n"
	"- Toggle wall distance*: 'W' key (only applicable if diagonal traversal is on)\n"
	"\n"
	"* Note: Unlike its 'D' cousin, 'W' can affect whether a solution is found\n"
	"at all - when enabled (default) it does not allow, the path (thin line) to\n"
	"touch any of the corners of a wall. This is done because usually, it would\n"
	"mean that a game object would partially \"clip\" into the wall as it went\n"
	"past, resulting in odd (to our eye) behaviour."
	;

	sgDrawColor4fv(&fill.r);
	sgDrawRectangle(border.x, border.y, WIDTH - border.x, HEIGHT - border.y, SG_TRUE);

	sgDrawColor4fv(&head.r);
	sgFontPrint(headf, border.x + margin.x, border.y + margin.y, headt);
	sgFontStrSize(headf, &csize.x, &csize.y, headt);

	sgDrawColor4fv(&line.r);
	sgDrawRectangle(border.x, border.y, WIDTH - border.x, HEIGHT - border.y, SG_FALSE);
	sgDrawLine(border.x, border.y + margin.y + csize.y / 2, WIDTH - border.x, border.y + margin.y + csize.y / 2);

	sgDrawColor4fv(&text.r);
	sgFontPrint(textf, border.x + margin.x, border.y + margin.y + csize.y, textt);
}

int main(void)
{
	sgLoadModule("SDL");
	sgLoadModule("OpenGL");
	sgLoadModule("Freetype");
	//sgLoadModule("DevIL");
	sgInit(WIDTH, HEIGHT, 32, 0);
	sgWindowSetTitle("SIEGE A-Star Demo - Hit 'F1' for instructions");

	SGFont* head = sgFontCreate("data/fonts/DejaVuSans.ttf", 16, 127);
	SGFont* text = sgFontCreate("data/fonts/DejaVuSans.ttf", 10, 127);

	score = sgFontCreate("data/fonts/DejaVuSans.ttf", cellw / 4.0, 127);

	SGNavGridData* data;
	SGList* path = NULL;
	size_t pathlen = 0;

	recreateGrid(SG_FALSE, SG_FALSE);

	SGint mx, my;

	SGEntity* handler = sgEntityCreate(1.0, SG_EVT_ALL);
	handler->evKeyboardKeyPress = evKeyboardKeyPress;
	handler->evKeyboardKeyRepeat = evKeyboardKeyPress;

    while(sgLoop(NULL))
    {
		sgMouseGetPos(&mx, &my);
		mx /= cellw;
		my /= cellh;
		if(0 <= mx && mx < GRIDW
		&& 0 <= my && my < GRIDH)
		{
			if(sgMouseGetButtonLeft())
			{
				sgNavGridAddWall(grid, mx, my);
				changed = SG_TRUE;
			}
			else if(sgMouseGetButtonRight())
			{
				sgNavGridAddClear(grid, mx, my);
				changed = SG_TRUE;
			}
			else if(sgKeyboardKey('1'))
			{
				data = grid->start->data;
				sgNavGridAddClear(grid, data->x, data->y);
				sgNavGridAddStart(grid, mx, my);
				changed = SG_TRUE;
			}
			else if(sgKeyboardKey('2'))
			{
				data = grid->goal->data;
				sgNavGridAddClear(grid, data->x, data->y);
				sgNavGridAddGoal(grid, mx, my);
				changed = SG_TRUE;
			}
		}
		if(changed)
		{
			resetScore(grid);
			sgNavGridSearchCreate(grid);
		}
		if(!instructions)
		{
			if(slow)
				sgNavGridSearchStep(grid);
			else
				while(!sgNavGridSearchStep(grid)) { }
		}
		path = sgNavGridSearchPath(grid, &pathlen);

		drawGrid(grid, SG_NAVGRID_CLEAR, ClearFillColor, SG_TRUE);
		drawGrid(grid, SG_NAVGRID_CLEAR, ClearLineColor, SG_FALSE);

		drawGrid(grid, SG_NAVGRID_WALL, WallFillColor, SG_TRUE);
		drawGrid(grid, SG_NAVGRID_WALL, WallLineColor, SG_FALSE);

		drawGrid(grid, SG_NAVGRID_START, StartFillColor, SG_TRUE);
		drawGrid(grid, SG_NAVGRID_START, StartLineColor, SG_FALSE);

		drawGrid(grid, SG_NAVGRID_GOAL, GoalFillColor, SG_TRUE);
		drawGrid(grid, SG_NAVGRID_GOAL, GoalLineColor, SG_FALSE);

		drawScore(grid, score, scores, sgColor4f(1.0, 1.0, 1.0, 1.0));

		if(slow || sgNavGridGoalFound(grid))
		{
			drawPath(path, PathFillColor, SG_FALSE, SG_TRUE);
			drawPath(path, PathLineColor, SG_FALSE, SG_FALSE);
			drawPath(path, PathLineColor, SG_TRUE, SG_FALSE);
		}

		if(instructions)
			drawInstructions(head, text, sgColor4f(0.0, 0.0, 0.0, 0.75), sgColor4f(0.5, 0.5, 0.5, 1.0), sgColor4f(1.0, 0.5, 0.0, 1.0), sgColor4f(1.0, 1.0, 1.0, 1.0));

		changed = SG_FALSE;

		sgWindowSwapBuffers();
		sgDrawClear();
	}

	sgFontDestroy(score);

	sgFontDestroy(text);
	sgFontDestroy(head);

	sgNavGridDestroy(grid);

	sgDeinit();

	return 0;
}

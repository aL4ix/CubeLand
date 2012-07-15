#include "../RadicalEngineOpenGL/RadicalEngine.h"

using namespace std;
#include "Cubemanager.cpp"
#include "Escenario.cpp"
#include "EvilCube.cpp"

//#include "menu.cpp"

void Matrix()
{
	GLfloat Matrix[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, (float*)Matrix);
	for(unsigned i=0; i<4; i++)
	{
		for(unsigned j=0; j<4; j++)
			cout << Matrix[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

class Font
{
public:
	unsigned space;
	unsigned height;
	const void* datos[9];
};

void printString(const Font& font, const char* Str)
{
	for(const char* s = Str; *s; s++)
	{
		if(*s == ' ')
			glBitmap(0, font.height, 0.0, 0.0, font.space, 0.0, NULL);
		else if('a' <= *s && *s <= 'z')
		{
			const unsigned* widthMin  = (const unsigned*)(font.datos[3]);
			const unsigned* iniposMin = (const unsigned*)(font.datos[4]);
			const GLubyte* rastersMin = (const GLubyte*)(font.datos[5]);
			unsigned c = *s-'a';
			glBitmap(widthMin[c], font.height, 0.0, 0.0, widthMin[c], 0.0, rastersMin+iniposMin[c]);
		}
		else if('A' <= *s && *s <= 'Z')
		{
			const unsigned* widthMay  = (const unsigned*)(font.datos[0]);
			const unsigned* iniposMay = (const unsigned*)(font.datos[1]);
			const GLubyte* rastersMay = (const GLubyte*)(font.datos[2]);
			unsigned c = *s-'A';
			glBitmap(widthMay[c], font.height, 0.0, 0.0, widthMay[c], 0.0, rastersMay+iniposMay[c]);
		}
		else if('0' <= *s && *s <= '9')
		{
			const unsigned* widthNum  = (const unsigned*)(font.datos[6]);
			const unsigned* iniposNum = (const unsigned*)(font.datos[7]);
			const GLubyte* rastersNum = (const GLubyte*)(font.datos[8]);
			unsigned c = *s-'0';
			glBitmap(widthNum[c], font.height, 0.0, 0.0, widthNum[c], 0.0, rastersNum+iniposNum[c]);
		}
	}
}

#include "Antipasto.cpp"

#include <ctime>

float spin = 0.0;
float speed = 0.03;
float spinJugador = 0.0;
float speedSpinCamera = 0.0;
float spinCamera;
Cube but;

Cube jugador(0.5);
Light luz;
Color luzBlanca;
Escenario escenario1;
vector<Cube> cubos;
float yInicio = 6.0;
EvilCube mother(jugador,escenario1);

ParticleAcc brincoJugador(jugador);
bool volando = false;
bool rebotado = false;
bool muerto = false;
bool suicidio = false;
Cube* jugadorPiso = NULL;
float nextPosX, nextPosZ;
float nextTime;
bool nextAvanzando = false;
float nextVelX, nextVelZ;
float magnitudCamaraMuerto = 8;
char  texto[255];
Buildings pared;

Poly menuLogo;
Poly menuArcade;
Poly menuSobrevive;
Poly menuSalir;
Poly menuFondo;

float tiempoInicio;

void DrawMenu();
void DrawGame1();
void DrawGame2();

void SetVolando(bool Volando)
{
	volando = Volando;
	if(volando)
	{
		brincoJugador.SetAcc(0, -0.3, 0);
	}
	else
	{
		brincoJugador.SetVel(0, 0, 0);
		brincoJugador.SetAcc(0, 0, 0);
		rebotado = false;
		jugadorPiso = NULL;
	}
}

void KeysMenu(unsigned char key, int x, int y);
void processNormalKeys(int key, int x, int y);

void realNormalKeys(unsigned char key, int x, int y)
{
	switch(key)
	{
		case ' ':
			if(muerto)
				return;
			brincoJugador.SetVel(0, 9, 0);
			SetVolando(true);
			processNormalKeys(32, x, y);
		break;
		case 27:
			SetVolando(true);
			jugador.Move(5, 6, 5);
			Pumpkin.SwitchTo2D();
			Radical.SetGameLoop(DrawMenu);
			glutKeyboardFunc(KeysMenu);
			EvilSons.cubes.clear();
			EvilSons.Llenar();
			pared = Buildings();
			pared.Triangulo();
			rebotado = false;
			muerto = false;
			suicidio = false;
			mother.tocoPiso = true;
			brincoJugador.SetAcc(0, 0, 0);
			spinCamera = 0;
		break;
	}
}

void processNormalKeys(int key, int x, int y)
{
	//bool plano1=false, plano2=false;
	cout <<key<<endl;
	switch (key){
		case 32:
			break;
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			spinJugador += M_PI;
			speedSpinCamera = M_PI;
			break;
		case GLUT_KEY_LEFT:
			spinJugador += M_PI/2;
			speedSpinCamera = M_PI/2;
			break;
		case GLUT_KEY_RIGHT:
			spinJugador -= M_PI/2;
			speedSpinCamera = -M_PI/2;
			break;
			
		default:
			return;
		}
		
	if(nextAvanzando)
		return;
	/*speedSpinJugador = float(float(X)-(float(Pumpkin.widthScreen)/2.0))/6000.0;
	av = (-150.0+float(Y)-float(Pumpkin.heightScreen)/2.0)/40.0;
	*/
	
	/*if (-1.5*X+480 >= Y) 
		plano1 = true;
	if (1.5*X <= Y) 
		plano2 = true;
	
	if(plano1==true && plano2==false)
	{
		//cout << "NORTE"<<endl;
	}
	if(plano1==false && plano2==true)
	{
		//cout << "SUR"<<endl;
		spinJugador += M_PI;
		speedSpinCamera = M_PI;
	}
	if(plano1==true && plano2==true)
	{
		//cout << "OESTE"<<endl;
		spinJugador += M_PI/2;
		speedSpinCamera = M_PI/2;
	}
	if(plano1==false && plano2==false)
	{
		//cout << "ESTE"<<endl;
		spinJugador -= M_PI/2;
		speedSpinCamera = -M_PI/2;
	}*/
	
	speedSpinCamera *= 2.0;
	nextPosX = floor(jugador.GetX())+0.5;
	nextPosZ = floor(jugador.GetZ())+0.5;
	nextTime = Schala.GetAbsTime();
	nextAvanzando = true;
	nextPosX -= sin(spinJugador);
	nextPosZ -= cos(spinJugador);
	//cout << "nx="<<nextPosX<<"nz="<<nextPosZ<<endl;
	nextVelX = nextPosX - jugador.GetX();
	nextVelZ = nextPosZ - jugador.GetZ();
	nextVelX *= 2.0;
	nextVelZ *= 2.0;
}

int InitGame()
{
	srand(time(NULL));
	
	luz.MoveW(1);
	luz.Move(5, 6, 5);
	
	jugador.Move(5, 6, 5);
	but.Move(5, 5, 5);
	
	Color luzBlanca = Color(1.0, 1.0, 1.0, 1.0);
	Color luzAmbient = Color(0.5, 0.5, 0.5, 1);
	//Color luzSpecular = Color(0.6, 0.6, 0.6, 1); 
	luz.SetAmbient(luzAmbient);
	luz.SetDifusse(luzBlanca);
	luz.SetSpecular(luzBlanca);
	escenario1 = Escenario::Escenario1();
	
	Color hey = Color(0.5, 0.5, 0.5, 1);
	Material::SetAmbientAndDifusse(hey);
	Material::SetSpecular(luzBlanca);
	Material::SetShininess(20);
	
	jugador.model.Scale(0.5, 2, 0.5);
	jugador.UpdateModel();
	
	cubos.push_back(Cube(0.95));
	cubos[cubos.size()-1].Move(5, yInicio, 5);
	
	mother.Init();
	
	mother.evil.Add(&luz);
	
	SetVolando(true);
	
	pared = Buildings();
	pared.Triangulo();
	
	Texture::InitEngine();
	//menu.Init();
	
	float facInc = 1.3, inc = 200;
	
	/*menuLogo = Poly::Rectangle(70*facInc+inc, 380*facInc, 250*facInc+inc, 410*facInc);
	menuLogo.SetTexture(logo);
	menuLogo.SetWholeTexture();
	
	menuArcade = Poly::Rectangle(100*facInc+inc, 260*facInc, 220*facInc+inc, 290*facInc);
	menuArcade.SetTexture(pioro);
	menuArcade.SetWholeTexture();
	
	menuSobrevive = Poly::Rectangle(100*facInc+inc, 190*facInc, 220*facInc+inc, 220*facInc);
	menuSobrevive.SetTexture(pioro);
	menuSobrevive.SetWholeTexture();
	
	menuSalir = Poly::Rectangle(100*facInc+inc, 130*facInc, 220*facInc+inc, 160*facInc);
	menuSalir.SetTexture(pioro);
	menuSalir.SetWholeTexture();*/
	
	menuFondo = Poly::Rectangle(0*facInc+inc, 0*facInc, 320*facInc+inc, 480*facInc);
	//menuFondo.SetTexture(menu);
	menuFondo.SetWholeTexture();
	
	//glutMouseFunc(mouse);
	//glutIdleFunc(display);
	glutKeyboardFunc(KeysMenu);
	
	Pumpkin.cameraLooking.Move(0, 5, 5);
	
	Pumpkin.Set2DWorld(800, 600, mrDontCare);
	Pumpkin.SwitchTo2D();
	Radical.SetGameLoop(DrawMenu);
	return 0;
}

void KeysMenu(unsigned char key, int x, int y)
{
	cout << "hey";
	switch(key)
	{
		case '1':
			Pumpkin.ReturnTo3D();
			Radical.SetGameLoop(DrawGame1);
			glutKeyboardFunc(realNormalKeys);
			glutSpecialFunc(processNormalKeys);
			tiempoInicio = Schala.GetAbsTime();
			break;
		case 27:
			exit(0);//glutLeaveMainLoop();
		default: 
			return;	
	}
}

void DrawMenu()
{
	Pumpkin.DrawBegin2D();
	
	glColor4f(1, 1, 1, 1);
	menuFondo.Draw();
	glColor4f(0, 0, 0, 1);
	menuLogo.Draw();
	menuArcade.Draw();
	menuSobrevive.Draw();
	menuSalir.Draw();
	
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos2i(200, 100);
	
	printString(Antipasto, texto);
	
	Pumpkin.DrawEnd();
}

void DrawGame1()
{
	spinCamera += Schala.Rel(speedSpinCamera);
	if(!rebotado)
		//jugador.MoveRel(av*sin(spinJugador), 0, av*cos(spinJugador));*/
		jugador.MoveTimeRel(nextVelX, 0, nextVelZ);
	
	brincoJugador.Acc();
	if(jugador.GetY() <= 0.0)
	{
		muerto = true;
		suicidio = true;
	}
	
	if(jugadorPiso)
		if(!jugadorPiso->CollisionXZ(jugador))
			SetVolando(true);
	
	if(volando)
	{
		for(unsigned i=0; i<escenario1.cubo.size(); i++)
			if(jugador.Collision(escenario1.cubo[i]))
			{
				SetVolando(false);
				jugadorPiso = &escenario1.cubo[i];
				jugador.MoveY(escenario1.cubo[i].GetY()+1);
				cout << "Piso";
				break;
			}
	}
		/*if(volando)
		{*/
			for(unsigned i=0; i<EvilSons.cubes.size(); i++)
				for(unsigned j=0; j<EvilSons.cubes[i].size(); j++)
					if(jugador.Collision(EvilSons.cubes[i][j]))
					{
						if(i == (unsigned) EvilSons.x && j == (unsigned) EvilSons.y)
							muerto = true;
						if(jugador.GetY()-0.3 >= EvilSons.cubes[i][j].GetY()+0.475) //Callo arriba del cubo
						{						
							//cout << "Choque";
							SetVolando(false);
							jugadorPiso = &EvilSons.cubes[i][j];
							jugador.MoveY(EvilSons.cubes[i][j].GetY()+1);
							jugadorPiso = &EvilSons.cubes[i][j];
						}
						else //rebote
						{
							//cout << "WOW\n";
							if(volando)
								rebotado = true;
							//jugador.MoveRel(-av*sin(spinJugador), 0, -av*cos(spinJugador));
							jugador.MoveTimeRel(-nextVelX, 0, -nextVelZ);
						}
						break;
					}
	//}
	
	if(nextAvanzando)
	{
		if(Schala.isElapsed(nextTime, .5))
		{
			nextAvanzando = false;
			nextVelX = nextVelZ = 0.0;
			speedSpinCamera = 0;
		}
	}
	
	jugador.Rotate(spinJugador*Math.RADTODEG, 0, 1, 0);
	
	spin += speed;
	
	Pumpkin.cameraPosition.Move(jugador.GetX()+8*sin(spinCamera),
								jugador.GetY()+6,
								jugador.GetZ()+8*cos(spinCamera));
	Pumpkin.cameraLooking.Move(jugador.GetX(),
								jugador.GetY()+4,
								jugador.GetZ());
	
	////////////////////
	Pumpkin.DrawBegin3D();
	
	Matrix();

	but.Draw();
	jugador.Draw();
	luz.Draw();
	escenario1.Dibujar();
	mother.Draw();
		
	Pumpkin.DrawEnd();
	////////////////////
	
	if(Schala.isElapsed(tiempoInicio, 5)){
		Radical.SetGameLoop(DrawGame2);
		EvilSons.cubes.clear();
		EvilSons.Llenar();
		SetVolando(true);
		jugadorPiso = NULL;
		}
		
}

void DrawGame2()
{	
	///////////////////////////////////////////////////////////////////////////
if(but.Collision(jugador))
	{
	//cout << "GANASTE cal:";
	sprintf (texto,"Construiste el %.0f%%",pared.Percentage());
	//cout << texto;
	magnitudCamaraMuerto  = 5+3*sin(spinCamera/3.0);
	Pumpkin.cameraPosition.Move(jugador.GetX()+magnitudCamaraMuerto*sin(spinCamera),
								jugador.GetY()+magnitudCamaraMuerto*sin(spinCamera/2.0),
								jugador.GetZ()+magnitudCamaraMuerto*cos(spinCamera));
	
	Pumpkin.cameraLooking.MoveY(jugador.GetY());
	spinCamera += 0.01;
	Schala.PauseThisFrame();
	
	}
	
	spinCamera += Schala.Rel(speedSpinCamera);
	if(!rebotado)
		//jugador.MoveRel(av*sin(spinJugador), 0, av*cos(spinJugador));*/
		jugador.MoveTimeRel(nextVelX, 0, nextVelZ);
	brincoJugador.Acc();
	if(jugador.GetY() <= 0.0)
	{
		muerto = true;
		suicidio = true;
	}
	
	if(jugadorPiso)
		if(!jugadorPiso->CollisionXZ(jugador))
			SetVolando(true);
	
	if(volando)
	{
		for(unsigned i=0; i<escenario1.cubo.size(); i++)
			if(jugador.Collision(escenario1.cubo[i]))
			{
				SetVolando(false);
				jugadorPiso = &escenario1.cubo[i];
				jugador.MoveY(escenario1.cubo[i].GetY()+1);
				cout << "Piso";
				break;
			}
	}
		/*if(volando)
		{*/
			for(unsigned i=0; i<EvilSons.cubes.size(); i++)
				for(unsigned j=0; j<EvilSons.cubes[i].size(); j++)
					if(jugador.Collision(EvilSons.cubes[i][j]))
					{
						if(i == (unsigned) EvilSons.x && j == (unsigned) EvilSons.y)
							muerto = true;
						if(jugador.GetY()-0.3 >= EvilSons.cubes[i][j].GetY()+0.475) //Callo arriba del cubo
						{						
							//cout << "Choque";
							SetVolando(false);
							jugadorPiso = &EvilSons.cubes[i][j];
							jugador.MoveY(EvilSons.cubes[i][j].GetY()+1);
							jugadorPiso = &EvilSons.cubes[i][j];
						}
						else //rebote
						{
							//cout << "WOW\n";
							if(volando)
								rebotado = true;
							//jugador.MoveRel(-av*sin(spinJugador), 0, -av*cos(spinJugador));
							jugador.MoveTimeRel(-nextVelX, 0, -nextVelZ);
						}
						break;
					}
	//}
	
	if(nextAvanzando)
	{
		if(Schala.isElapsed(nextTime, .5))
		{
			nextAvanzando = false;
			nextVelX = nextVelZ = 0.0;
			speedSpinCamera = 0;
		}
	}
	
if(muerto){
	//cout << "MURISTESS!!\n";
	
	//pared.ShowMatrix(pared.modelo);
	//exit(0);
	sprintf (texto,"Construiste el %.0f X100to",pared.Percentage());
	
	
	magnitudCamaraMuerto  = 5+3*sin(spinCamera/3.0);
	Pumpkin.cameraPosition.Move(jugador.GetX()+magnitudCamaraMuerto*sin(spinCamera),
								jugador.GetY()+magnitudCamaraMuerto*sin(spinCamera/2.0),
								jugador.GetZ()+magnitudCamaraMuerto*cos(spinCamera));
	
	Pumpkin.cameraLooking.MoveY(jugador.GetY());
	spinCamera += 0.01;
	Schala.PauseThisFrame();
}
else
{
	Pumpkin.cameraPosition.Move(jugador.GetX()+8*sin(spinCamera),
								jugador.GetY()+6,
								jugador.GetZ()+8*cos(spinCamera));
	Pumpkin.cameraLooking.Move(jugador.GetX(),
								jugador.GetY()+4,
								jugador.GetZ());
}
	
	mother.Process();
	
	jugador.Rotate(spinJugador*Math.RADTODEG, 0, 1, 0);
	
	spin += speed;
	//luz.MoveTo(5.0*cos(spin)+5.0, 6.0, 5.0*sin(spin)+5.0);
		
	
	////////////////////
	Pumpkin.DrawBegin3D();

	but.Draw();
	jugador.Draw();
	luz.Draw();
	escenario1.Dibujar();
	mother.Draw();
	
		
	Pumpkin.DrawEnd();
	////////////////////
}

/***********************************************************************/
int main()
{
	InitGame();
	Radical.StartGame(DrawMenu, 500, 500);
	cout << "Mikey es gason";
	return 0;
}

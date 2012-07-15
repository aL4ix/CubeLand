
#include "Buildings.cpp"

class EvilCube
{
public:
	const static float yInicio = 10.0;
	
	EvilCube(Cube& Jugador, Escenario& Piso) : jugador(Jugador), piso(Piso), factorRebote(0.2), velCaida(5.0)
	{
	}
	
	void Init()	
	{
		
		count = 0;
		tocoPiso = true;
		mother.Resize(.95);
		evil.Add(&mother);
		
		evil.Move(0, yInicio, 0);//jugador.GetX(), yInicio, jugador.GetZ());

		time = Schala.GetAbsTime();
		aluminio.SetColor(1, 1, 1, 1);
		oro.SetColor(1, .5, .5, 1);
		x0 = y0 = 0.0;
		motherParado = true;
		ultimoRebotando = false;
		
	}
	
	void Process()
	{
		x1 = floor(jugador.GetX())+0.5;
		y1 = floor(jugador.GetZ())+0.5;
		
		if(motherParado)
		{
			if(x1!=x0 || y1 != y0){
				//mother.SetVel(1, 0, 1));
				//evil.MoveRel(x1-x0, 0, y1-y0);
				distanciaObjetivo = Math.Distance2D(evil.GetX(), evil.GetZ(), x1, y1);
				motherParado = false;
//				evil.MoveTo(floor(jugador.GetX())+0.5, yInicio, floor(jugador.GetZ())+0.5);
			}
		}
		else
		{
			velMotherX = 1*(x1-evil.GetX());
			velMotherY = 1*(y1-evil.GetZ());
			distanciaObjetivo = Math.Distance2D(evil.GetX(), evil.GetZ(), x1, y1);
			evil.MoveTimeRel(velMotherX, 0, velMotherY);
			if(Math.Distance2D(x0, y0, evil.GetX(), evil.GetZ()) > distanciaObjetivo)
			   {
				   motherParado = true;
				   x0 = x1;
				   y0 = y1;
				   //time = Schala.GetSysTime();
				   evil.Move(x1, yInicio, y1);
			   }
		}
		
		if(ultimoRebotando)
		{
			//cout << "ultimoRebotando\n";
			rebote->Acc();
			//EvilSons.GetLastOne().ProcessCollisions();
			if(EvilSons.GetLastOne().GetY() <= cuboAColisionar->GetY()+1) //cuboAColisionar->Collision(EvilSons.GetLastOne()))
			{
				//cout << "ultimoRebotandoCol\n";
				//EvilSons.GetLastOne().SetY(cuboAColisionar->GetY()+0.95);
				//cout << "Vel="<<rebote->velY<<"fac="<<factorRebote;
				float disminuye = factorRebote*rebote->velY;
				//cout << "res="<<disminuye<<endl;
				rebote->SetVel(0, -(disminuye), 0);
				//rebote->Vel();
				if(rebote->velY < 0.1)
				{
					//cout << "ultimoRebotandoFIN\n";
					EvilSons.GetLastOne().MoveY(cuboAColisionar->GetY()+0.95);
					delete rebote;
					tocoPiso=true;
					EvilSons.x = -1;
					EvilSons.y = -1;
					time = Schala.GetAbsTime();
					ultimoRebotando = false;
				
					return;
				}
			}
			
			return;
		}
		if(tocoPiso)
		{
			if(Schala.isElapsed(time, .5) && motherParado)
			{
				//cubos.push_back(Cube());
				//cubos[count].Init(0.95);
				//cubos[count].MoveTo(jugador.GetX(), yInicio, jugador.GetZ());
				//count++;
				EvilSons.addCube(evil.GetX(), yInicio, evil.GetZ());
				tocoPiso = false;
				time = Schala.GetAbsTime();
			}
		}
		else
		{
			Cube& cubo = EvilSons.GetLastOne();//cubos[count-1];
			cubo.MoveTimeRel(0, -velCaida, 0);
			for(unsigned i=0; i<EvilSons.cubes.size(); i++)
				for(unsigned j=0; j<EvilSons.cubes[i].size(); j++)
				{
					if(i == (unsigned) EvilSons.x && j == (unsigned) EvilSons.y)
						continue;
					if(cubo.Collision(EvilSons.cubes[i][j]))
					{
						//cout << "ColEvilSon\n";
						ultimoRebotando = true;
						cubo.MoveY(EvilSons.cubes[i][j].GetY()+0.95);
						cuboAColisionar = &EvilSons.cubes[i][j];
						rebote = new ParticleAcc(cubo);
						rebote->SetVel(0, factorRebote*velCaida, 0);
						rebote->SetAcc(0, -1, 0);
						return;
						//goto loQueNoDeberiaDeHacer_EsProgramarBienChafa;
					}
			
			}
			for(unsigned i=0; i< piso.cubo.size(); i++){
				if(cubo.Collision(piso.cubo[i]))
				{
					//cout << "ColPiso\n";
					ultimoRebotando = true;
					cubo.MoveY(piso.cubo[i].GetY()+0.95);
					cuboAColisionar = &piso.cubo[i];
					rebote = new ParticleAcc(cubo);
					rebote->SetVel(0, factorRebote*velCaida, 0);
					rebote->SetAcc(0, -1, 0);
					return;
					//goto loQueNoDeberiaDeHacer_EsProgramarBienChafa;
				}
				
			}
		}
		//loQueNoDeberiaDeHacer_EsProgramarBienChafa:;
		
	}
	
	void Draw()
	{
		EvilSons.drawCubes();
		/*for(unsigned i=0; i<count; i++)
			cubos[i].Draw();*/
			
		Material::SetAmbientAndDifusse(oro);
		//Material::SetSpecular(aluminio);
		evil.Draw();
		Material::SetAmbientAndDifusse(aluminio);
	}
	
//protected:
	//Cube evil;
	DrawableGroup evil;
	Cube mother;
	//vector<Cube> cubos;
	vector<Color> colores;
	//vector<vector<Cube> > cubos;
	unsigned count;
	Cube& jugador;
	bool tocoPiso;
   float time;
	Escenario& piso;
	Color aluminio;
	Color oro;
	//ParticleVel movSuaveMother;
	float x0,y0,x1,y1;
	bool motherParado;
	float distanciaObjetivo;
	float velMotherX;
	float velMotherY;
	bool ultimoRebotando;
	ParticleAcc* rebote;
	Cube* cuboAColisionar;
	float factorRebote;
	float velCaida;
};

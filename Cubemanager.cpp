#include <map>

class CubeManager {

	const static int max = 30;
public:
	vector<vector<Cube> > cubes;
	vector<Color> colores;
	int x,y;
	
	
	CubeManager(){
		
		Llenar();
	
		for (int i=0; i<max; i++)
			colores.push_back(Color(randomColor(),randomColor(), randomColor()));
		//cout << randomColor();
		x=0;
	}
	
	void Llenar()
	{
		for (int i=0; i<max; i++) 
			cubes.push_back(vector<Cube>());
	}
	
	void  addCube(float X, float Y, float Z) {
		x = rand()%max;
		cubes[x].push_back(Cube());
		y = cubes[x].size()-1;
		Cube& ultimo = cubes[x][y];
		ultimo.Resize(0.95);
		ultimo.Move(X,Y,Z);
	}
	
	Cube& GetLastOne(){
		return cubes[x][y];
	}
	

	float randomColor(){
		return float(rand())/RAND_MAX;//32767.0;//return (float(random())/2147483647.0);
	}
	
	void drawCubes(){
		//cout<< "INICIO"<< endl;
		for (int i=0; i<max; i++){
			Material::SetAmbientAndDifusse(colores[i]);			
			for(unsigned j=0; j<cubes[i].size(); j++){
				cubes[i][j].Draw();
				//cout <<cubes[i][j].GetX()<<","<<cubes[i][j].GetY()<<","<<cubes[i][j].GetZ()<<endl;
			
			}
			
			
			
				
		}
	}
	
} EvilSons;



class Buildings {
public:
	vector<vector<vector<bool> > > original;
	vector<vector<vector<bool> > > modelo;
	int longx, longy, longz;
	int piso;
	
	Buildings(){
		longx=10;
		longy=10;
		longz=10;
		piso = 0;
		
		
		
		
	
	}
	
	void Llenar(vector<vector<vector<bool> > > &mat)
	{
		for (int x=0; x<longx; x++) {
			vector<vector<bool> > v;
			for (int z=0; z < longz ; z++) {
				vector <bool> v1;
				for(int y=0; y<longy; y++)
				{
					v1.push_back(false);
				}
				v.push_back(v1);
			}
			mat.push_back(v);
		}
	}
	
	
	
	void ShowMatrix(vector<vector<vector<bool> > > &mat){
		cout << "WAAAAAAAAAAAAAAAA"<<endl;
		for(int y=0; y<10; y++){
			cout << "piso: "<< y<<endl;
			for(int z=0; z<10; z++){
				for(int x=0; x<10; x++){
					cout << mat[x][z][y]<< " ";
				}
				cout<<endl;
			}
		}
	
	
	
	}
	
	
	void GetMatrix()
	{
		original.clear();
		Llenar(original);
		for(unsigned i=0; i<EvilSons.cubes.size(); i++)
			for(unsigned j=0; j<EvilSons.cubes[i].size(); j++)
			{
				float x = EvilSons.cubes[i][j].GetX();
				float z = EvilSons.cubes[i][j].GetZ();
				float y = EvilSons.cubes[i][j].GetY();
				
				//cout<< x<<" "<< y<<" "<< z<<" "<<"part0"<<endl;
				
				x = x-0.472;
				z = z-0.472;
				y = (y-0.472)/0.95;
				
				//cout<< x<<" "<< y<<" "<< z<<" "<<"part1"<<endl;
				
				
				x = floor(x*10.0);
				z = floor(z*10.0);
				y = floor(y*10.0);
				
				unsigned xx = x, zz = z, yy = y;
				
				unsigned xxx = xx/10, zzz = zz/10, yyy = yy/10;
				
				if(xx % 10 >= 5)
					xxx++;
				if(zz % 10 >= 5)
					zzz++;
				if(yy % 10 >= 5)
					yyy++;
				
				cout<< xxx<<" "<< yyy<<" "<< zzz<<" "<<"part2"<<endl;
				
				original[xxx][zzz][yyy] = true;
			}
	}
	

	void Triangulo()
	{	
		Llenar(modelo);
		const char *matrix[] =
		{
			"0000000000",
			"0000000000",
			"0000000000",
			"0000000000",
			"0001110000",
			"0001110000",
			"0001110000",
			"0000000000",
			"0000000000",
			"0000000000"
		};
		Construir(matrix);
		Construir(matrix);
		Construir(matrix);
		/*Construir(matrix);
		Construir(matrix);
		Construir(matrix);
		Construir(matrix);
		Construir(matrix);
		*/
		
	
	}
	void Cubo()
	{	
		Llenar(modelo);
		const char *matrix[] =
		{
			"1111111111",
			"1000000001",
			"1000000001",
			"1000000001",
			"1000000001",
			"1000000001",
			"1000000001",
			"1000000001",
			"1000000001",
			"1111111111"
		};
		Construir(matrix);
		Construir(matrix);
		Construir(matrix);
		/*Construir(matrix);
		 Construir(matrix);
		 Construir(matrix);
		 Construir(matrix);
		 Construir(matrix);
		 */
		
		
	}
	
	inline void Construir(const char *matrix[])
	{
		
		for(unsigned y=0; y<10; y++)
		{
			for(unsigned x=0; x<10; x++)
			{
				if(matrix[y][x] == '0')
					continue;
				modelo[x][y][piso]=true;					

				float diametroCubo = 0.95;
				float medio = diametroCubo*0.5;
				float separacion = 1.0;
				EvilSons.addCube(x*separacion+medio, piso*diametroCubo+medio, y*separacion+medio);
			}
		}
		
		
		piso++;
	}
	
	
	float  Percentage()
	{
		//ShowMatrix(modelo);
		GetMatrix();
		int peso=0, total=0;
		for (int x=0; x <longx; x++) 
			for (int z=0; z < longz; z++) 
				for(int y=0; y< longy; y++){
					if(modelo[x][z][y] ==true)
						total++;
					if(original[x][z][y] ==true)
					{
						if(modelo[x][z][y] == original[x][z][y])
							peso++;
						else
							total++;
					}
						
					
					
				}
					total--;
					return (peso*100)/total;
	} 
	
};

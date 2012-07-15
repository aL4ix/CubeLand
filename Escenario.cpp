
#include <vector>
#include <functional>

class Escenario
{
public:
	Escenario()
	{
		diametroCubo = 0.95;
		separacion = 1.0;
		aluminio.SetColor(1, 1, 1);
	}
	static Escenario Escenario1()
	{
		
		vector<vector<bool> > res;
		const unsigned mx = 10;
		const unsigned my = 10;
		
		int matrix[][mx] =
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
		for(unsigned x=0; x<mx; x++)
		{
			vector<bool> v;
			for(unsigned y=0; y<my; y++)
			{
				v.push_back(bool(matrix[y][x]));
			}
			res.push_back(v);
		}
		Escenario esc;
		esc.Construir(res);
		return esc;
	}
	
	inline void Construir(vector<vector<bool> > matrix)
	{
		for(unsigned x=0; x<matrix.size(); x++)
		{
			for(unsigned y=0; y<matrix[x].size(); y++)
			{
				if(matrix[x][y] == false)
					continue;
				cubo.push_back(Cube(diametroCubo));
				float medio = diametroCubo*0.5;
				cubo[cubo.size()-1].Move(x*separacion+medio, -0.475, y*separacion+medio);
			}
		}
	}
	inline void Dibujar()
	{
		Material::SetAmbientAndDifusse(aluminio);
		for(unsigned i=0; i<cubo.size(); i++)
			cubo[i].Draw();
	}
//protected:
	vector<Cube> cubo;
	float diametroCubo;
	float separacion;
	Color aluminio;
};

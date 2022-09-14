#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//singular structure
struct worker
{
	string name;
	string surname;
	string job;
	int age;
};

//our database
vector <worker> staff = {};

//makes worker structure zeroed out to default state
void nullWorker(worker &wn)
{
	wn = {"","","",0};
}

//directly adds a worker to database
void addWorker(worker wrk)
{
	staff.push_back(wrk);
}

//handles adding a worker from menu
void addWorkerProc()
{
	string req;
	string name;
	string surname;
	string job;
	int age;
	printf("Input Name:\n");
	getline(cin, name);
	printf("Input Surname:\n");
	getline(cin, surname);
	printf("Input Job Position:\n");
	getline(cin, job);
	printf("Input Age:\n");
	getline(cin, req);
	age = atoi(req.c_str());
	addWorker({ name,surname,job,age });
}

//directly removes worker from database by id
void removeWorker(int id)
{
	staff.erase(staff.begin()+id);
}

//handles worker removal via call from main menu
void removeWorkerProc()
{
	string req;
	printf("Input ID:\n");
	getline(cin, req);
	removeWorker(atoi(req.c_str()));
}

//prints out entire database
void printWorkers()
{
	int i = 0;
	for (worker wrk : staff)
	{
		printf("ID: %d\nName: %s\nSurname: %s\nPosition: %s\nAge: %d\n", 
			i, wrk.name.c_str(), wrk.surname.c_str(),
			wrk.job.c_str(),wrk.age);
		i++;
	}
}

//saves database to file
void saveWorkers()
{
	ofstream wdata("database.wdb");

	for (worker wrk : staff)
	{
		wdata << "#name=" << wrk.name.c_str() << ";" <<
			"sname=" << wrk.surname.c_str() << ";" <<
			"job=" << wrk.surname.c_str() << ";" <<
			"age=" << wrk.age << ";@";
	}
	wdata.close();
	cout << "Database saved\n";
}

//loads database from file
void loadWorkers()
{
	ifstream wdata("database.wdb");
	if (!wdata.is_open())
	{
		printf("Could not open file!\n");
		return;
	}

	printf("Reading Database...\n");

	string fdata = "";
	string cline = "";
	int rw = 0;
	string word1 = "";
	string word2 = "";
	worker cw;
	nullWorker(cw);

	while (getline(wdata, cline))
	{
		fdata += cline;
	}

	int l = fdata.length();	
	   
	for (int i = 0; i < l; i++)
	{
		if (fdata[i] == '#')
		{
			nullWorker(cw);
		} 
		else if (fdata[i] == '@')
		{
			addWorker(cw);
			printf("Adding worker: %s %s %s %d\n",
				cw.name.c_str(), cw.surname.c_str(), 
				cw.job.c_str(), cw.age);
			rw = 0;
			word1 = "";
			word2 = "";
		}
		else 
		{
			if ((fdata[i] != '=') && (fdata[i] != ';'))
			{
				if (rw == 0) word1 += fdata[i];
				if (rw == 1) word2 += fdata[i];
			}
			if (fdata[i] == '=')
			{
				rw = 1;
			}
			if (fdata[i] == ';')
			{
				rw = 0;
				if (word1 == "name") {
					cw.name = word2;					
				}
				if (word1 == "sname") {
					cw.surname = word2;
				}
				if (word1 == "age") {
					cw.age = atoi(word2.c_str());
				}
				if (word1 == "job") {
					cw.job = word2.c_str();
				}
				word1 = "";
				word2 = "";
			}
			
		}

	}

	wdata.close();
}


int main()
{
	bool work=true;

	while (work)
	{
		printf("1 - Add; 2 - Remove; 3 - Print; 4 - Save; 5 - Load; 0 - Quit\n");
		string resp = "";
		getline(cin, resp);
		int r = atoi(resp.c_str());

		switch (r)
		{
		case 0:
		{
			work = false;
			break;
		}
		case 1:
		{
			addWorkerProc();
			break;
		}
		case 2:
		{
			removeWorkerProc();
			break;
		}
		case 3:
		{
			printWorkers();
			break;
		}
		case 4:
		{
			saveWorkers();
			break;
		}
		case 5:
		{
			loadWorkers();
			break;
		}

		}
	
	}

	system("pause");
}
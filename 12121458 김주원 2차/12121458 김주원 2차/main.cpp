#include<iostream>
#include<fstream>
#include<list>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;

int k; // 학생 수.

// 학생 한 명의 정보를 나타내는 클래스.
class student 
{
public:
	int id; // 학번 (1000~2999)
	char name[25]; // 이름
	int age; // 10~50

};

student students[3000]; // 학생들의 정보를 저장할 배열.(1000~2999)만 사용할 예정.)

bool network[3000][3000];// network[i][j] : i는 j에게 연락가능.


// 파일에서 학생들의 정보를 입력받는 함수.
void getInfo(ifstream& in)
{
	in >> k;
	for (int i = 0; i < k; i++)
	{
		// 각 학생들의 이름과 나이, 학번을 세팅.
		in >> students[1000 + i].name;
		in >> students[1000 + i].age;
		students[1000 + i].id = 1000 + i;
		network[1000 + i][1000 + i] = true;
	}
	cout << endl;
}

// 표준입출력으로 테스트하는 데 이용한 함수.
void getInfo()
{
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		// 각 학생들의 이름과 나이, 학번을 세팅.
		cin >> students[1000 + i].name;
		cin >> students[1000 + i].age;
		students[1000 + i].id = 1000 + i;
		network[1000 + i][1000 + i] = true;
	}
	cout << endl;
}

// "I" 명령을 수행하는 함수.
void commandI()
{
	int M, N;
	cin >> M >> N;

	// M이 N의 전화번호를 알게 됨
	network[M][N] = true;

}

// Floyd-Warshall 알고리즘을 통해 transitive closure를 만든다.
void Floyd_Warshall()
{
	for (int i = 1000; i < 1000 + k; i++)
	{
		for (int j = 1000; j < 1000 + k; j++)
		{// i에게 연락할 수 있는 j는
			if (network[j][i])
			{ // i가 연락할 수 있는 사람들에게 연락을 할 수 있다.
				for (int t = 1000; t < 1000 + k; t++)
				{
					if (network[i][t])
						network[j][t] = true;
				}
			}
		}
	}
}

// "O"명령을 수행하는 함수.
void commandO()
{
	int S;
	cin >> S;

	// Floyd_Warshall 알고리즘을 수행해서 transitive closure를 만든다.
	Floyd_Warshall();

	// 서로 연락가능한 학생을 찾아 가장 작은 학번을 출력.
	for (int i = 1000; i < 1000 + k; i++)
	{
		if (network[i][S] && network[S][i])
		{
			cout << i << endl;
			return;
		}
	}
}



int main()
{
	clock_t start_time, end_time;
	double elapsedTime;
	start_time = clock();

	// network 벡터를 assign.
	//network.assign(3000, vector<bool>(3000, false));


	//입력파일 이름을 입력받은 후 open.
	ifstream inFile;
	cout << "입력파일의 이름을 입력하세요 : ";
	char inputFileName[50];
	cin >> inputFileName;
	inFile.open(inputFileName);
	
	//cout << inFile.is_open() << endl;

	getInfo(inFile);
	
	// 입력파일의 사용이 끝났으므로 close.
	inFile.close();



	char cmd;
	while (1)// Q가 입력될 때까지 명령어를 입력받아 수행한다.
	{
		cin >> cmd;
		switch (cmd)
		{
		case'I':
			commandI();
			break;

		case'O':
			commandO();
			break;

		case'Q':
			// 걸린 시간을 출력 후 종료.
			end_time = clock();
			elapsedTime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
			cout << elapsedTime << endl;
			return 0;
		}
	}
	
}
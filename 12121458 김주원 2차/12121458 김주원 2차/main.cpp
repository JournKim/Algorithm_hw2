#include<iostream>
#include<fstream>
#include<list>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;

int k; // �л� ��.

// �л� �� ���� ������ ��Ÿ���� Ŭ����.
class student 
{
public:
	int id; // �й� (1000~2999)
	char name[25]; // �̸�
	int age; // 10~50

};

student students[3000]; // �л����� ������ ������ �迭.(1000~2999)�� ����� ����.)

bool network[3000][3000];// network[i][j] : i�� j���� ��������.


// ���Ͽ��� �л����� ������ �Է¹޴� �Լ�.
void getInfo(ifstream& in)
{
	in >> k;
	for (int i = 0; i < k; i++)
	{
		// �� �л����� �̸��� ����, �й��� ����.
		in >> students[1000 + i].name;
		in >> students[1000 + i].age;
		students[1000 + i].id = 1000 + i;
		network[1000 + i][1000 + i] = true;
	}
	cout << endl;
}

// ǥ����������� �׽�Ʈ�ϴ� �� �̿��� �Լ�.
void getInfo()
{
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		// �� �л����� �̸��� ����, �й��� ����.
		cin >> students[1000 + i].name;
		cin >> students[1000 + i].age;
		students[1000 + i].id = 1000 + i;
		network[1000 + i][1000 + i] = true;
	}
	cout << endl;
}

// "I" ����� �����ϴ� �Լ�.
void commandI()
{
	int M, N;
	cin >> M >> N;

	// M�� N�� ��ȭ��ȣ�� �˰� ��
	network[M][N] = true;

}

// Floyd-Warshall �˰����� ���� transitive closure�� �����.
void Floyd_Warshall()
{
	for (int i = 1000; i < 1000 + k; i++)
	{
		for (int j = 1000; j < 1000 + k; j++)
		{// i���� ������ �� �ִ� j��
			if (network[j][i])
			{ // i�� ������ �� �ִ� ����鿡�� ������ �� �� �ִ�.
				for (int t = 1000; t < 1000 + k; t++)
				{
					if (network[i][t])
						network[j][t] = true;
				}
			}
		}
	}
}

// "O"����� �����ϴ� �Լ�.
void commandO()
{
	int S;
	cin >> S;

	// Floyd_Warshall �˰����� �����ؼ� transitive closure�� �����.
	Floyd_Warshall();

	// ���� ���������� �л��� ã�� ���� ���� �й��� ���.
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

	// network ���͸� assign.
	//network.assign(3000, vector<bool>(3000, false));


	//�Է����� �̸��� �Է¹��� �� open.
	ifstream inFile;
	cout << "�Է������� �̸��� �Է��ϼ��� : ";
	char inputFileName[50];
	cin >> inputFileName;
	inFile.open(inputFileName);
	
	//cout << inFile.is_open() << endl;

	getInfo(inFile);
	
	// �Է������� ����� �������Ƿ� close.
	inFile.close();



	char cmd;
	while (1)// Q�� �Էµ� ������ ��ɾ �Է¹޾� �����Ѵ�.
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
			// �ɸ� �ð��� ��� �� ����.
			end_time = clock();
			elapsedTime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
			cout << elapsedTime << endl;
			return 0;
		}
	}
	
}
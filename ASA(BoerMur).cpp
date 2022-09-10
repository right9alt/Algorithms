#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int alphabetSIZE = 256;


vector<int> BM(string str, string subStr)
{
	int m = subStr.size();
	int n = str.size();
	vector <int> chars(alphabetSIZE, -1);
	vector <int> arr;

	// Заполняем таблицу символов подстроки.
	for (int i = 0; i < m; i++) {
		chars[(int)subStr[i]] = i; // Последнее вхождение символа в строку.
	}

	int s = 0; // Сдвиг подстроки по отношению к строке.
	while (s <= (n - m)) {
		int j = m - 1;

		while (j >= 0 && subStr[j] == str[s + j]) { // Подстрока в строке - уменьшаем сдвиг.
			j--;
		}

		if (j < 0) { // Если есть вхождение.
			arr.push_back(s); // Помещаем номер символа строки в массив.
			s += (s + m < n) ? m - chars[str[s + m]] : 1;
		}
		else {
			s += max(1, j - chars[str[s + j]]);
		}
	}

	return arr;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	string s, pattern;
	cout << "Введите строку: "; getline(cin, s);
	cout << "Введите подстроку: "; getline(cin, pattern);
	vector<int> answer;
	answer = BM(s, pattern);
	cout << "Результат: ";
	for (int i = 0; i < answer.size(); ++i) {
		cout << "\nПодстрока найдем на позиции: " << answer[i];
	}
	
}

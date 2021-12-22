#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
const char name_symbols[] = "�������������������������������������Ũ��������������������������-";
const char date_symbols[] = "0123456789.";
const char numbers[] = "0123456789";
struct student
{
	char last_name[32];
	unsigned room, group;
	unsigned day, month, year; // ���� �������� � ���������
};

int get_key() // ������ ���� �������: ����� ������� - ���������� � ���
{
	int key = getch();
	if (key == 0 || key == 224)
		key = getch();
	return key;
}

int esc_enter_menu(const char* msg) // ���� esc-enter (�������������/�������/������)
{
	system("cls");
	printf("%s\nENTER\t��\nESC\t���\n", msg);
	while (true)
	{
		int key = get_key();
		if (key == 13 || key == 27)
			return key;
	}
}

bool esc_enter(const char* msg) // ������ esc - enter ��� �������������/������� � �.�.
{
	while (true)
	{
		int menu = esc_enter_menu(msg);
		system("cls");
		switch (menu)
		{
		case 27:
			return false;
		case 13:
			return true;
		}
	}
}

bool unsigned_check(char* str) // ��������, ��� � ���� ��� ����� ��� ���������� ���������
{
	unsigned size = strlen(str) + 1;
	unsigned i = 0;
	while (i < size)
	{
		if (strchr(numbers, str[i]) == NULL)
		{
			return false;
		}
		i++;
	}
	return true;
}

bool get_unsigned(unsigned* i, const char* msg) // ������ ������ ������������ ����� � ��������� �� �������� ������
{
	char str[21];
	while (true)
	{
		printf("������� %s: ", msg);
		gets_s(str, 20); // ���� ����� � ������
		fflush(stdin);
		if (unsigned_check(str))
		{
			*i = (unsigned)atoi(str);
			return true;
		}
		else
		{
			if (!esc_enter("������������ ���� �����. ���������?"))
				return false;
		}
	}
	
}

bool last_name_check(char* str) // ��������, ��� � ���� ��� ������� ��� ����������� ��������
{
	unsigned size = strlen(str);
	unsigned i = 0;
	while (i < size)
	{
		if (strchr(name_symbols, str[i]) == 0)
			return false;
		i++;
	}
	return true;
}

bool get_str(char *string, const char* msg, unsigned size, bool last_name) // ������ ����� ������
{
	char str[256];
	while (true)
	{
		printf("������� %s", msg);
		memset(str, 0, sizeof(str));
		gets_s(str, size);
		fflush(stdin);
		if ((last_name))
		{
			if (!last_name_check(str))
			{
				if (!esc_enter("������������ ���� �������. ���������?"))
					return false;
			}
			else
				break;
		}
		else
			break;
	}
	strcpy(string, str);
	return true;
}

bool leap_year(unsigned year) // �������� �� ���������� ���
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

bool date_check(unsigned day, unsigned month, unsigned year) // �������� �� ������������ ���� (�.�. ���� �� ���� �������� ���� 31 ������� ��� 45.84.99999)
{
	if (year >= 1900 && year <= 2100)
	{
		if (month >= 1 && month <= 12)
		{
			if (day >= 1 && day <= 31)
			{
				switch (month)
				{
				case 2:
				{
					bool leap = leap_year(year);
					if ((leap && day > 29) || (!leap && day > 28))
						return false;
					break;
				}
				case 4:
					if (day > 30)
						return false;
					break;
				case 6:
					if (day > 30)
						return false;
					break;
				case 9:
					if (day > 30)
						return false;
					break;
				case 11:
					if (day > 30)
						return false;
					break;
				}
				return true;
			}
		}
	}
	return false;
}

bool date_format_check(char* str, unsigned size) // ��������, ��� � ������ ������� ���� ������ ����� � ���� '-'
{
	unsigned i = 0;
	while (i < size)
	{
		if (strchr(date_symbols, str[i]) == 0)
			return false;
		i++;
	}
	return true;
}

bool get_date(unsigned *day, unsigned *month, unsigned *year, const char* msg) // ������ ���� (� ��������� �������)
{
	while (true)
	{
		printf("������� %s (� ������� dd.mm.yyyy): ", msg);
		unsigned tmp_day, tmp_month, tmp_year;
		char str[20];
		fgets(str, sizeof(str), stdin);
		unsigned i = strlen(str);
		if (i >= 8  && i <= 11 && sscanf(str, "%u.%u.%u", &tmp_day, &tmp_month, &tmp_year) == 3)
		{
			if (date_check(tmp_day, tmp_month, tmp_year))
			{
				*day = tmp_day;
				*month = tmp_month;
				*year = tmp_year;
				return true;
			}
			else
				if (!esc_enter("������� �������������� ����! ��������� ����?"))
					return false;
		}
		else
			if (!esc_enter("������������ ������ ��������� ����! ��������� ����?"))
				return false;
	}
}

bool create_new_data(student* data, int n, int s)
{
	/* �������� ����� ������ ����� �������,
	���� ������ fasle - ������ � ��.
	������ true ������ � ������ ������ �������� ���� ������ */
	student add;
	if (get_str(add.last_name, "������� ��������: ", 31, true))
	{
		if (get_unsigned(&add.room, "����� ������� ��������"))
		{
			if (get_unsigned(&add.group, "����� ������ ��������"))
			{
				if (get_date(&add.day, &add.month, &add.year, "���� �������� �������� � ���������"))
				{
					data = (student*)realloc(data, ((s + 1) * sizeof(student)));
					while (s > n)
					{
						data[s] = data[s - 1];
						s--;
					}
					data[n] = add;
					system("cls");
					return true;
				}
			}
		}
	}
	system("cls");
	printf("������ �������� ����� ������.\n\n");
	return false;
}

void delete_data(student* data, int n, int count) // �������� ���������� ������ ����� ������ ���������� ������ � ������� � �.�.
{
	while (n < count)
	{
		data[n] = data[n + 1];
		n++;
	}
	if (count <= 1)
		free(data);
	else
		data = (student*)realloc(data, ((count-1)) * sizeof(student));
}

void abc_sort(student* sort, int count) // ���������� ������� �� ��������
{
	for (int i = 1; i < count; i++)
	{
		for (int j = 0; j < count - i; j++)
		{
			if (stricmp(sort[j].last_name, sort[j + 1].last_name) > 0)
			{
				student tmp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = tmp;
			}
		}
	}
}

int date_sort(student* sort_data, int count) // ���������� �� �������� ����
{
	while (true)
	{
		unsigned sort_day, sort_month, sort_year;
		if (!get_date(&sort_day, &sort_month, &sort_year, "���� ��� ������ � ����� ���� ���������,\n������������ � ��������� ������� ��������� ����"))
			return -5;
		system("cls");
		int i = 0;
		while (i < count)
		{
			if ((sort_data[i].year == sort_year && sort_data[i].month == sort_month && sort_data[i].day > sort_day)
				|| (sort_data[i].year == sort_year && sort_data[i].month > sort_month) || sort_data[i].year > sort_year)
				i++;
			else
			{
				delete_data(sort_data, i, count);
				count--;
			}
		}
		if (count == 0)
			return -6; // ��� ������ ��. ������;
		return count; // ������� ���������� ������� �� ������
	}
}

int save_data(student** data, int count, bool sort) // ���������� ������
{
	student* save_data = (student*)malloc(count * sizeof(student));
	save_data = *data;
	int save_count = count;
	if (sort) // ���� ��������� true - �������� � �����������
	{
		abc_sort(save_data, save_count);
		save_count = date_sort(save_data, save_count);
		if (save_count < 0)
			return save_count; // ������ ��� ������
	}
	char filename[256] = { '\0' };
	get_str(filename, "����� ����� ��� ����������:\n", 255, false);
	FILE* output = fopen(filename, "w");
	if (output)
	{
		for (int i = 0; i < save_count; i++)
		{
			fprintf(output, "%s\t%u\t%u\t%u.%u.%u", save_data[i].last_name, save_data[i].room, save_data[i].group, save_data[i].day, save_data[i].month, save_data[i].year);
			if (i < save_count - 1)
				fprintf(output, "\n");
		}
	}
	else
	{
		free(save_data);
		return -4; // ��� ������ ����������
	}
	free(save_data);
	fclose(output);
	return -3; // ��� ��������� ����������
}

int read_data(student** data, int* count) // ������ ������ �� �����
{
	student* read_data = NULL;
	student tmp;
	char filename[256] = { '\0' };
	get_str(filename, "����� ����� ��� ������ ������:\n", 255, false);
	FILE* status = fopen(filename, "r");
	int n = 0;
	if (status)
	{
		while (!feof(status))
		{
			int e = fscanf(status, "%s\t%u\t%u\t%u.%u.%u", tmp.last_name, &tmp.room, &tmp.group, &tmp.day, &tmp.month, &tmp.year);
			if (e == 6 && date_check(tmp.day, tmp.month, tmp.year))
			{
				n++;
				read_data = (student*)realloc(read_data, (n * sizeof(student)));
				read_data[n - 1] = tmp;
			}
			else
			{
				fclose(status);
				free(read_data);
				return -2; // ��� ������
			}
		}
	}
	else
		return -1; // ��� ������
	*count = n;
	*data = read_data;
	fclose(status);
	return n; // ������ ���������� ��������� ������� � ��� ������/��������� ������
}

void print_current(student* data) // ������� �� ����� ������� ������
{
	printf("�������:\t%s\n����� �������:\t%u\n����� ������:\t%u\n���� ��������:\t%u.%u.%u", data->last_name, data->room, data->group, data->day, data->month, data->year);
	printf("\n=======================================\n");
}

int edit_menu(student* data) // ���� ��������� ������, ������ �������
{
	system("cls");
	print_current(data);
	printf("F1\t�������� �������\n"
		"F2\t�������� ����� �������\n"
		"F3\t�������� ����� ������\n"
		"F4\t�������� ���� ��������\n"
		"ESC\t�������� �����\n");
	while (true)
	{
		int key = get_key();
		if (key == 59 || key == 60 || key == 61 || key == 62 || key == 27)
			return key;
	}
}

void edit_data(student* data) // ��. edit_menu
{
	while (true)
	{
		int menu = edit_menu(data);
		printf("=======================================\n");
		system("cls");
		if (menu == 27)
			break;
		switch (menu)
		{
		case 59:
			get_str(data->last_name, "����� ������� ��������: ", 31, true);
			break;
		case 60:
			get_unsigned(&(data->room), "����� ����� ������� ��������");
			break;
		case 61:
			get_unsigned(&(data->group), "����� ����� ������ ��������");
			break;
		case 62:
			get_date(&(data->day), &(data->month), &(data->year), "����� ���� �������� �������� � ���������");
			break;
		}
	}
}

int main_menu(student* data, int count, int current) // �������� ����. ����� ������� ������, ��������� �� �������, ��������, ���������� ��������� ������
{
	if (count > 0)
	{
		print_current(data + current);
		if (count > 1)
		{
			if (current != 0 && current != count - 1)
				printf("<-\t��������� �� �������\t->\n\n");
			if (current == 0)
				printf("  \t��������� �� �������\t->\n\n");
			if (current == count - 1)
				printf("<-\t��������� �� �������\t  \n\n");
		}
		printf("ENTER\t������������� ������� ������\n"
			"DEL\t������� ������� ������\n");
	}
	else
		printf("������� �� �����������\n\n");
	printf("INS\t�������� ����� ������\n"
		"ESC\t�������� � ������� ����\n");
	while (true)
	{
		int key = get_key();
		if ((count > 0 && (key == 75 || key == 77 || key == 83 || key == 13)) || key == 82 || key == 27)
			return key;
	}
}

void main_info(student* data, int* s) // ��. main_menu
{
	int current = 0, count = *s;
	if (count == 0)
	{
		current = -1;
	}
	while (true)
	{
		int menu = main_menu(data, count, current);
		system("cls");
		if (menu == 27)
		{
			*s = count;
			break;
		}
		switch (menu)
		{
		case 75:
			if (current > 0)
				current--;
			break;
		case 77:
			if (current < count - 1)
				current++;
			break;
		case 83:
			delete_data(data, current, count);
			if (count > 0)
			{
				count--;
				if (current == count)
					current--;
			}
			break;
		case 13:
			edit_data(data + current);
			break;
		case 82:
			if (create_new_data(data, current + 1, count))
				count++, current++;
			break;
		}
	}
}

int start_menu(int count) // ��������� ����. ��������, �������� ������������� � �� ������������� ������
{
	while (true)
	{
		printf("SPACE\t��������� ������ �� �����\n"
			"ENTER\t������ � �������\n");
		if (count > 0)
		{
			printf("F1\t��������� ������ � ����\n"
				"F2\t��������� ��������� ��������� � ����\n");
		}
		printf("ESC\t����� �� ���������");
		int key = get_key();
		system("cls");
		if (((count > 0) && (key == 59 || key == 60)) || key == 13 || key == 32 || key == 27)
			return key;
	}
}

void message(int n) // ����� ������ ��� ������ ����������� ��������
{
	system("cls");
	if (n > 0)
		printf("������ �� ����� �� ���������� ������ ������� �������!\n");
	else
	{
		switch (n)
		{
		case 0:
			printf("���� �� ���������� ������ �� �������� ������.\n");
			break;
		case -1:
			printf("������ ������ �����!\n");
			break;
		case -2:
			printf("������������ ��������� ������ �����!\n");
			break;
		case -3:
			printf("������ ������� ��������� �� ���������� ������.\n");
			break;
		case -4:
			printf("������ ������������ ������ �� ���������� ������.\n");
			break;
		case -5:
			printf("������ ���������� ������.\n");
			break;
		case -6:
			printf("����� ��������� ���� ��� ������ ��� ����������.\n");
			break;
		}
	}
	printf("===========================\n");
}

int main() // ��. start_menu
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	student *data = NULL;
	int count = 0;
	while (true)
	{
		int menu = start_menu(count);
		switch (menu)
		{
		case 27:
			if (esc_enter("�� ������������� ������ ��������� ������ ���������?\n"))
			{
				free(data);
				return 0;
			}
			system("cls");
			break;
		case 32:
			message(read_data(&data, &count));
			break;
		case 59:
			message(save_data(&data, count, false));
			break;
		case 60:
			message(save_data(&data, count, true));
			break;
		case 13:
			main_info(data, &count);
			break;
		}
	}
}
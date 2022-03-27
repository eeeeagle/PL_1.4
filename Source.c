#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
const char name_symbols[] = "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß-";
const char date_symbols[] = "0123456789.";
const char numbers[] = "0123456789";
struct student
{
	char last_name[32];
	unsigned room, group;
	unsigned day, month, year; // äàòà ïðîïèñêè â îáùåæèòèè
};

int get_key() // çàïðîñ êîäà êëàâèøè: æìåøü êëàâèøó - âîçâðàùàåò å¸ êîä
{
	int key = getch();
	if (key == 0 || key == 224)
		key = getch();
	return key;
}

int esc_enter_menu(const char* msg) // ìåíþ esc-enter (ïîäòâåðæäåíèÿ/ïîâòîðà/îòìåíû)
{
	system("cls");
	printf("%s\nENTER\tÄà\nESC\tÍåò\n", msg);
	while (true)
	{
		int key = get_key();
		if (key == 13 || key == 27)
			return key;
	}
}

bool esc_enter(const char* msg) // çàïðîñ esc - enter äëÿ ïîäòâåðæäåíèÿ/ïîâòîðà è ò.ä.
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

bool unsigned_check(char* str) // ïðîâåðêà, ÷òî â ïîëå äëÿ ÷èñëà íåò ïîñòîðîíèõ ýëåìåíòîâ
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

bool get_unsigned(unsigned* i, const char* msg) // çàïðîñ ëþáîãî áåççíàêîâîãî ÷èñëà ñ ïðîâåðêîé íà ââîäèìûå äàííûå
{
	char str[21];
	while (true)
	{
		printf("Ââåäèòå %s: ", msg);
		gets_s(str, 20); // ââîä ÷èñëà â ñòðîêó
		fflush(stdin);
		if (unsigned_check(str))
		{
			*i = (unsigned)atoi(str);
			return true;
		}
		else
		{
			if (!esc_enter("Íåêîððåêòíûé ââîä ÷èñëà. Ïîâòîðèòü?"))
				return false;
		}
	}
	
}

bool last_name_check(char* str) // ïðîâåðêà, ÷òî â ïîëå äëÿ ôàìèëèè íåò ïîñòîðîííèõ ñèìâîëîâ
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

bool get_str(char *string, const char* msg, unsigned size, bool last_name) // çàïðîñ ëþáîé ñòðîêè
{
	char str[256];
	while (true)
	{
		printf("Ââåäèòå %s", msg);
		memset(str, 0, sizeof(str));
		gets_s(str, size);
		fflush(stdin);
		if ((last_name))
		{
			if (!last_name_check(str))
			{
				if (!esc_enter("Íåêîððåêòíûé ââîä ôàìèëèè. Ïîâòîðèòü?"))
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

bool leap_year(unsigned year) // ïðîâåðêà íà âèñîêîñíûé ãîä
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

bool date_check(unsigned day, unsigned month, unsigned year) // ïðîâåðêà íà êîððåêòíîñòü äàòû (ò.å. äàáû íå áûëî ïðèêîëîâ òèïî 31 ôåâðàëÿ èëè 45.84.99999)
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

bool date_format_check(char* str, unsigned size) // ïðîâåðêà, ÷òî â ñòðîêå çàïðîñà åñòü òîëüêî öèôðû è çíàê '-'
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

bool get_date(unsigned *day, unsigned *month, unsigned *year, const char* msg) // çàïðîñ äàòû (ñ ïðîâåðêîé ôîðìàòà)
{
	while (true)
	{
		printf("Ââåäèòå %s (â ôîðìàòå dd.mm.yyyy): ", msg);
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
				if (!esc_enter("Ââåäåíà íåñóùåñòâóþùàÿ äàòà! Ïîâòîðèòü ââîä?"))
					return false;
		}
		else
			if (!esc_enter("Íåêîððåêòíûé ôîðìàò ââåäåííîé äàòû! Ïîâòîðèòü ââîä?"))
				return false;
	}
}

bool create_new_data(student* data, int n, int s)
{
	/* ñîçäàíèå íîâîé çàïèñè ïîñëå òåêóùåé,
	åñëè âåðíåò fasle - óäàëèò å¸ æå.
	âåðíåò true òîëüêî â ñëó÷àå óñïåõà çàïðîñîâ âñåõ äàííûõ */
	student add;
	if (get_str(add.last_name, "ôàìèëèþ ñòóäåíòà: ", 31, true))
	{
		if (get_unsigned(&add.room, "íîìåð êîìíàòû ñòóäåíòà"))
		{
			if (get_unsigned(&add.group, "íîìåð ãðóïïû ñòóäåíòà"))
			{
				if (get_date(&add.day, &add.month, &add.year, "äàòó ïðîïèñêè ñòóäåíòà â îáùåæèòèè"))
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
	printf("Îøèáêà ñîçäàíèÿ íîâîé çàïèñè.\n\n");
	return false;
}

void delete_data(student* data, int n, int count) // óäàëåíèå ïåðåäàííîé çàïèñè ïóòåì çàïèñè ñëåäóþùèåé çàïèñè â òåêóùóþ è ò.ä.
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

void abc_sort(student* sort, int count) // ñîðòèðîâêà çàïèñåé ïî àëôàâèòó
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

int date_sort(student* sort_data, int count) // ñîðòèðîâêà ïî ââîäèìîé äàòå
{
	while (true)
	{
		unsigned sort_day, sort_month, sort_year;
		if (!get_date(&sort_day, &sort_month, &sort_year, "äàòó äëÿ çàïèñè â íîâûé ôàéë ñòóäåíòîâ,\nïîñåëèâøèõñÿ â îáùåæèòèè ïîçäíåå óêàçàííîé äàòû"))
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
			return -6; // êîä îøèáêè ñì. ñòðîêó;
		return count; // âîçâðàò êîëè÷åñòâà çàïèñåé íà çàïèñü
	}
}

int save_data(student** data, int count, bool sort) // ñîõðàíåíèå äàííûõ
{
	student* save_data = (student*)malloc(count * sizeof(student));
	save_data = *data;
	int save_count = count;
	if (sort) // åñëè ïåðåäàííî true - ñîõðàíèå ñ ñîðòèðîâêîé
	{
		abc_sort(save_data, save_count);
		save_count = date_sort(save_data, save_count);
		if (save_count < 0)
			return save_count; // âåðíåò êîä îøèáêè
	}
	char filename[256] = { '\0' };
	get_str(filename, "àäðåñ ôàéëà äëÿ ñîõðàíåíèÿ:\n", 255, false);
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
		return -4; // êîä îøèáêè ñîõðàíåíèÿ
	}
	free(save_data);
	fclose(output);
	return -3; // êîä óñïåøíîãî ñîõðàíåíèÿ
}

int read_data(student** data, int* count) // ÷òåíèå äàííûõ èç ôàéëà
{
	student* read_data = NULL;
	student tmp;
	char filename[256] = { '\0' };
	get_str(filename, "àäðåñ ôàéëà äëÿ ÷òåíèÿ äàííûõ:\n", 255, false);
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
				return -2; // êîä îøèáêè
			}
		}
	}
	else
		return -1; // êîä îøèáêè
	*count = n;
	*data = read_data;
	fclose(status);
	return n; // âåðíåò êîëè÷åñòâî ñ÷èòàííûõ çàïèñåé è êîä îøèáêè/óñïåøíîãî ÷òåíèÿ
}

void print_current(student* data) // âûâîäèò íà ýêðàí òåêóùóþ çàïèñü
{
	printf("Ôàìèëèÿ:\t%s\nÍîìåð êîìíàòû:\t%u\nÍîìåð ãðóïïû:\t%u\nÄàòà ïðîïèñêè:\t%u.%u.%u", data->last_name, data->room, data->group, data->day, data->month, data->year);
	printf("\n=======================================\n");
}

int edit_menu(student* data) // ìåíþ èçìåíåíèÿ çàïèñè, çàïðîñ êëàâèøè
{
	system("cls");
	print_current(data);
	printf("F1\tÈçìåíèòü ôàìèëèþ\n"
		"F2\tÈçìåíèòü íîìåð êîìàíòû\n"
		"F3\tÈçìåíèòü íîìåð ãðóïïû\n"
		"F4\tÈçìåíèòü äàòó ïðîïèñêè\n"
		"ESC\tÂåðíóòñÿ íàçàä\n");
	while (true)
	{
		int key = get_key();
		if (key == 59 || key == 60 || key == 61 || key == 62 || key == 27)
			return key;
	}
}

void edit_data(student* data) // ñì. edit_menu
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
			get_str(data->last_name, "íîâóþ ôàìèëèþ ñòóäåíòà: ", 31, true);
			break;
		case 60:
			get_unsigned(&(data->room), "íîâûé íîìåð êîìíàòû ñòóäåíòà");
			break;
		case 61:
			get_unsigned(&(data->group), "íîâûé íîìåð ãðóïïû ñòóäåíòà");
			break;
		case 62:
			get_date(&(data->day), &(data->month), &(data->year), "íîâóþ äàòó ïðîïèñêè ñòóäåíòà â îáùåæèòèè");
			break;
		}
	}
}

int main_menu(student* data, int count, int current) // îñíîâíîå ìåíþ. âûâîä òåêóùåé çàïèñè, íàâèãàöèÿ ïî çàïèñÿì, óäàëåíèå, äîáàâëåíèå èçìåíåíèå çàïèñè
{
	if (count > 0)
	{
		print_current(data + current);
		if (count > 1)
		{
			if (current != 0 && current != count - 1)
				printf("<-\tÍàâèãàöèÿ ïî çàïèñÿì\t->\n\n");
			if (current == 0)
				printf("  \tÍàâèãàöèÿ ïî çàïèñÿì\t->\n\n");
			if (current == count - 1)
				printf("<-\tÍàâèãàöèÿ ïî çàïèñÿì\t  \n\n");
		}
		printf("ENTER\tÐåäàêòèðîâàòü òåêóùóþ çàïèñü\n"
			"DEL\tÓäàëèòü òåêóùóþ çàïèñü\n");
	}
	else
		printf("Çàïèñåé íå îáíàðóæåííî\n\n");
	printf("INS\tÄîáàâèòü íîâóþ çàïèñü\n"
		"ESC\tÂåðíóòñÿ â ãëàâíîå ìåíþ\n");
	while (true)
	{
		int key = get_key();
		if ((count > 0 && (key == 75 || key == 77 || key == 83 || key == 13)) || key == 82 || key == 27)
			return key;
	}
}

void main_info(student* data, int* s) // ñì. main_menu
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

int start_menu(int count) // íà÷àëüíîå ìåíþ. çàãðóçêà, âûãðóçêà ñîðòèðîâàííûõ è íå ñîðòèðîâàííûõ äàííûõ
{
	while (true)
	{
		printf("SPACE\tÇàãðóçèòü äàííûå èç ôàéëà\n"
			"ENTER\tÐàáîòà ñ äàííûìè\n");
		if (count > 0)
		{
			printf("F1\tÑîõðàíèòü äàííûå â ôàéë\n"
				"F2\tÑîõðàíèòü ðåçóëüòàò îáðàáîòêè â ôàéë\n");
		}
		printf("ESC\tÂûõîä èç ïðîãðàììû");
		int key = get_key();
		system("cls");
		if (((count > 0) && (key == 59 || key == 60)) || key == 13 || key == 32 || key == 27)
			return key;
	}
}

void message(int n) // âûâîä îøèáêè èëè óñïåõà âûïîëíåííîé îïåðàöèè
{
	system("cls");
	if (n > 0)
		printf("Äàííûå èç ôàéëà ïî óêàçàííîìó àäðåñó óñïåøíî ñ÷èòàíû!\n");
	else
	{
		switch (n)
		{
		case 0:
			printf("Ôàéë ïî óêàçàííîìó àäðåñó íå ñîäåðæèò äàííûõ.\n");
			break;
		case -1:
			printf("Îøèáêà ÷òåíèÿ ôàéëà!\n");
			break;
		case -2:
			printf("Íåêîððåêòíàÿ ñòðóêòóðà äàííûõ ôàéëà!\n");
			break;
		case -3:
			printf("Äàííûå óñïåøíî ñîõðàíåíû ïî óêàçàííîìó àäðåñó.\n");
			break;
		case -4:
			printf("Îøèáêà ñîõðàíåíåíèÿ äàííûõ ïî óêàçàííîìó àäðåñó.\n");
			break;
		case -5:
			printf("Îòìåíà ñîõðàíåíèÿ äàííûõ.\n");
			break;
		case -6:
			printf("Ïîñëå óêàçàííîé äàòû íåò äàííûõ äëÿ ñîõðàíåíèÿ.\n");
			break;
		}
	}
	printf("===========================\n");
}

int main() // ñì. start_menu
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
			if (esc_enter("Âû äåéñòâèòåëüíî õîòèòå çàâåðøèòü ðàáîòó ïðîãðàììû?\n"))
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

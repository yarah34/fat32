#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "fat32header.h"

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	char dataBuffer[512];

	FAT32_BootRecord *pFAT32_BootRecord = (FAT32_BootRecord*)dataBuffer;

	//wchar_t* MediaType = L"\\\\.\\K:";

	// Ввод буквы носителя с консоли
	char MediaType1;
	char MediaType[64]; // массив
	wcout << L"Enter letter of holder" << endl;
	cin >> MediaType1;
	sprintf(MediaType,"\\\\.\\%c:",MediaType1); //выводит форм. данные в строку


	HANDLE fileHandle = CreateFile(
		MediaType, // Имя файла/устройства (wchar*)
		GENERIC_READ, // режим доступа
		FILE_SHARE_READ | FILE_SHARE_WRITE, //Режим совместной работы
		NULL, // Атрибуты безопасности
		OPEN_EXISTING, //способ открытия
		FILE_ATTRIBUTE_NORMAL, //флаги и атрибуты
		NULL
		//Описатель (идентификатор) файла шаблона с правами доступа GENERIC_READ
		);

	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = 0; //чтобы позиционироваться в начале

		// Задать позицию
		unsigned long currentPosition = SetFilePointer(
			  fileHandle,
			  sectorOffset.LowPart,// младшая часть LARGE_INTEGER
			  &sectorOffset.HighPart, // старшая часть
			  FILE_BEGIN
		// Точка в файле, относительно которой необходимо позиционироваться
		// (FILE_BEGIN, FILE_CURRENT, FILE_END)
			);
			if(currentPosition == sectorOffset.LowPart)
			{
				DWORD bytesToRead = 512; // сколько нужно считать
				DWORD bytesRead; // сколько удалось считать

				// Чтение данных
				bool readResult = ReadFile(
					  fileHandle, // дескриптор
					  dataBuffer, // куда читаем данные
					  bytesToRead,
					  &bytesRead,
					  NULL //ручное управление буферизацией
					);
					if(readResult == false || bytesRead != bytesToRead)
						{
							cout << "Error bytesRead" << endl;
							return 1;
						} else
						{
							wcout << L"Successfull bytesRead" << endl;
							printf("OEM name \t\t\t\t\t\t\t\t %s\n", pFAT32_BootRecord->OEM_Name);
							wprintf(L"Количество байт в секторе\t\t\t\t\t         %u\n", pFAT32_BootRecord->SectorSize);
							wprintf(L"Количество секторов в кластере (кластерный множитель) \t                 %u\n", pFAT32_BootRecord->ClusterSize);
							wprintf(L"Размер зарезервированной области (в секторах)\t\t\t\t %u\n", pFAT32_BootRecord->ReservedAreaSize);
							wprintf(L"Количество копий FAT \t\t\t\t\t\t         %u\n", pFAT32_BootRecord->NumberCopiesFat);
							wprintf(L"Максимальное кол-во 32-байтовых записей в корневом каталоге \t\t %u\n", pFAT32_BootRecord->MaxNumberRecRootCat);
							wprintf(L"16-разрядное кол-во секторов в ФС \t\t\t\t\t %u\n", pFAT32_BootRecord->ShestSectorsCount);
							wprintf(L"Количество секторов в дорожке \t\t\t\t\t         %u\n", pFAT32_BootRecord->NumberSectTrack);
							wprintf(L"Количество головок \t\t\t\t\t\t\t %u\n", pFAT32_BootRecord->NumberHeads);
							wprintf(L"Количество секторов перед началом раздела \t\t\t\t %u\n", pFAT32_BootRecord->NumbSectBfStartSection);
							wprintf(L"32-разрядное кол-во секторов в ФС \t\t\t\t\t %u\n", pFAT32_BootRecord->Numb32SectFat);
							wprintf(L"32-разрядный размер FAT в секторах \t\t\t\t\t %u\n", pFAT32_BootRecord->FatSize32);
							wprintf(L"Кластер, в котором находится корневой каталог \t\t\t\t %u\n", pFAT32_BootRecord->ClusterRootCatOffset);
							wprintf(L"Сектор, в котором находится резервная копия загрузочного сектора\t %u\n", pFAT32_BootRecord->SectReservCopyBootSector);

						}


			} else
			{
				cout << "Error of position" << endl;
				return 1;
			}


	} else {
		cout << "Invalid handle value" << endl;
		return 1;
	}

	CloseHandle(fileHandle);
    system("pause");
	return 1;
}


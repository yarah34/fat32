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

	// ���� ����� �������� � �������
	char MediaType1;
	char MediaType[64]; // ������
	wcout << L"Enter letter of holder" << endl;
	cin >> MediaType1;
	sprintf(MediaType,"\\\\.\\%c:",MediaType1); //������� ����. ������ � ������


	HANDLE fileHandle = CreateFile(
		MediaType, // ��� �����/���������� (wchar*)
		GENERIC_READ, // ����� �������
		FILE_SHARE_READ | FILE_SHARE_WRITE, //����� ���������� ������
		NULL, // �������� ������������
		OPEN_EXISTING, //������ ��������
		FILE_ATTRIBUTE_NORMAL, //����� � ��������
		NULL
		//��������� (�������������) ����� ������� � ������� ������� GENERIC_READ
		);

	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = 0; //����� ����������������� � ������

		// ������ �������
		unsigned long currentPosition = SetFilePointer(
			  fileHandle,
			  sectorOffset.LowPart,// ������� ����� LARGE_INTEGER
			  &sectorOffset.HighPart, // ������� �����
			  FILE_BEGIN
		// ����� � �����, ������������ ������� ���������� �����������������
		// (FILE_BEGIN, FILE_CURRENT, FILE_END)
			);
			if(currentPosition == sectorOffset.LowPart)
			{
				DWORD bytesToRead = 512; // ������� ����� �������
				DWORD bytesRead; // ������� ������� �������

				// ������ ������
				bool readResult = ReadFile(
					  fileHandle, // ����������
					  dataBuffer, // ���� ������ ������
					  bytesToRead,
					  &bytesRead,
					  NULL //������ ���������� ������������
					);
					if(readResult == false || bytesRead != bytesToRead)
						{
							cout << "Error bytesRead" << endl;
							return 1;
						} else
						{
							wcout << L"Successfull bytesRead" << endl;
							printf("OEM name \t\t\t\t\t\t\t\t %s\n", pFAT32_BootRecord->OEM_Name);
							wprintf(L"���������� ���� � �������\t\t\t\t\t         %u\n", pFAT32_BootRecord->SectorSize);
							wprintf(L"���������� �������� � �������� (���������� ���������) \t                 %u\n", pFAT32_BootRecord->ClusterSize);
							wprintf(L"������ ����������������� ������� (� ��������)\t\t\t\t %u\n", pFAT32_BootRecord->ReservedAreaSize);
							wprintf(L"���������� ����� FAT \t\t\t\t\t\t         %u\n", pFAT32_BootRecord->NumberCopiesFat);
							wprintf(L"������������ ���-�� 32-�������� ������� � �������� �������� \t\t %u\n", pFAT32_BootRecord->MaxNumberRecRootCat);
							wprintf(L"16-��������� ���-�� �������� � �� \t\t\t\t\t %u\n", pFAT32_BootRecord->ShestSectorsCount);
							wprintf(L"���������� �������� � ������� \t\t\t\t\t         %u\n", pFAT32_BootRecord->NumberSectTrack);
							wprintf(L"���������� ������� \t\t\t\t\t\t\t %u\n", pFAT32_BootRecord->NumberHeads);
							wprintf(L"���������� �������� ����� ������� ������� \t\t\t\t %u\n", pFAT32_BootRecord->NumbSectBfStartSection);
							wprintf(L"32-��������� ���-�� �������� � �� \t\t\t\t\t %u\n", pFAT32_BootRecord->Numb32SectFat);
							wprintf(L"32-��������� ������ FAT � �������� \t\t\t\t\t %u\n", pFAT32_BootRecord->FatSize32);
							wprintf(L"�������, � ������� ��������� �������� ������� \t\t\t\t %u\n", pFAT32_BootRecord->ClusterRootCatOffset);
							wprintf(L"������, � ������� ��������� ��������� ����� ������������ �������\t %u\n", pFAT32_BootRecord->SectReservCopyBootSector);

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


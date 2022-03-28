#pragma pack(push, 1)
typedef struct
{
	char Padding1[3];
	char OEM_Name[8];
	unsigned short SectorSize;
	unsigned char ClusterSize;
	// ���������� ��������� (���-�� �������� � ��������)
	unsigned short ReservedAreaSize;
	unsigned char NumberCopiesFat;
	unsigned short MaxNumberRecRootCat;
	// ����. ���-�� 32-����. ������� � �������� ��������
	unsigned short ShestSectorsCount;
	//16-����. ���-�� �������� � ��
	char MediaType;
	// ��� ��������
	unsigned short FatSize16;
	unsigned short NumberSectTrack;
	// ���-�� �������� � �������
	unsigned short NumberHeads;
	// ���-�� �������
	unsigned int NumbSectBfStartSection;
	// ���-�� �������� ����� ������� �������
	unsigned int Numb32SectFat;
	// 32-��������� ���-�� �������� ��
	unsigned int FatSize32;
	unsigned int ClusterRootCatOffset;
	// �������,  ������� ��������� �������� �������
	unsigned short SectReservCopyBootSector;
	// ������, � ������� ��������� ����� ����.�������


} FAT32_BootRecord;
#pragma pack (pop)

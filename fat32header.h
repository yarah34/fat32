#pragma pack(push, 1)
typedef struct
{
	char Padding1[3];
	char OEM_Name[8];
	unsigned short SectorSize;
	unsigned char ClusterSize;
	// Кластерный множитель (кол-во секторов в кластере)
	unsigned short ReservedAreaSize;
	unsigned char NumberCopiesFat;
	unsigned short MaxNumberRecRootCat;
	// Макс. кол-во 32-байт. записей в корневом каталоге
	unsigned short ShestSectorsCount;
	//16-разр. кол-во секторов в ФС
	char MediaType;
	// Тип носителя
	unsigned short FatSize16;
	unsigned short NumberSectTrack;
	// Кол-во секторов в дорожке
	unsigned short NumberHeads;
	// Кол-во головок
	unsigned int NumbSectBfStartSection;
	// Кол-во секторов перед началом раздела
	unsigned int Numb32SectFat;
	// 32-разрядное кол-во секторов ФС
	unsigned int FatSize32;
	unsigned int ClusterRootCatOffset;
	// Кластер,  котором находится корневой каталог
	unsigned short SectReservCopyBootSector;
	// Сектор, в котором резервная копия загр.сектора


} FAT32_BootRecord;
#pragma pack (pop)

#include<iostream>
#include <stdlib.h>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

struct TIME
{
	int Ngay;
	int Thang;
	int Nam;
};

struct THUOC
{
	int Ma_Thuoc;
	string Ten_Thuoc;
	string Trieu_Chung;
	int So_Luong;
	float Gia_Thuoc;
};

struct KHACH_HANG
{
	TIME ngay_mua;
	string name;
	int year;
	string so_dien_thoai;
	string dia_chi;
	string ten_thuoc;
	int so_lan;
	float gia_tien;
};

struct NODE
{
	THUOC data1;
	KHACH_HANG data2;
	struct NODE* pNext;
};

struct LIST
{
	NODE* pHead;
	NODE* pTail;
};

void KhoiTaoDanhSach(LIST & list)
{
	list.pHead = NULL;
	list.pTail = NULL;
}

NODE* KhoiTaoNodeThuoc(THUOC x)
{
	NODE* p = new NODE;
	if (p == NULL)
	{
		cout << "\nCap phat that bai !";
		return NULL;
	}
	p->data1 = x;
	p->pNext = NULL;
	return p;
}

NODE* KhoiTaoNodeKhachHang(KHACH_HANG x)
{
	NODE* p = new NODE;
	if (p == NULL)
	{
		cout << "\nCap phat that bai !";
		return NULL;
	}
	p->data2= x;
	p->pNext = NULL;
	return p;
}

bool isEmpty(LIST & list)
{
	if (list.pHead != NULL)
		return list.pHead = NULL;
}

void Clear()
{
	system("pause");
	system("cls");
}

void ThemCuoi(LIST & list, NODE* p)
{
	if (list.pHead == NULL)
	{
		list.pHead = list.pTail = p;
	}
	else
	{
		list.pTail->pNext = p;
		list.pTail = p;
	}
}

string Chi_Lay_Ten(string ten)
{
	int length = ten.length();
	int i;
	for (i = length - 1; i >= 0; i--)
	{
		if (ten[i] == ' ')
		{
			break;
		}
	}
	return ten.substr(i + 1);
}

//------------------------------------------------------------------------------------------------------------------------
void Doc_Thong_Tin_1_Loai_Thuoc (fstream & filein, THUOC & thuoc)
{
	filein >> thuoc.Ma_Thuoc;
	filein.seekg(1, 1);
	getline(filein, thuoc.Ten_Thuoc, ';');
	getline(filein, thuoc.Trieu_Chung, ';');
	filein >> thuoc.So_Luong;
	filein.seekg(1, 1);
	filein >> thuoc.Gia_Thuoc;
	string temp;
	getline(filein, temp);
}

void Doc_Danh_Sach_Thuoc(fstream& filein, LIST& list)
{
	while (!filein.eof())
	{
		THUOC thuoc;
		Doc_Thong_Tin_1_Loai_Thuoc(filein, thuoc);
		NODE* p = KhoiTaoNodeThuoc(thuoc);
		ThemCuoi(list, p);
	}
}

void Xuat_Thong_Tin_1_Loai_Thuoc(THUOC thuoc)
{
	cout << "Ma thuoc: " << thuoc.Ma_Thuoc << endl;
	cout << "Ten thuoc: " << thuoc.Ten_Thuoc << endl;
	cout << "Trieu chung dung thuoc: " << thuoc.Trieu_Chung << endl;
	cout << "So luong thuoc trong kho: " << thuoc.So_Luong << endl;
	cout << "Gia tien thuoc: " << thuoc.Gia_Thuoc<< " VND" << endl;
}

void Xuat_Thong_Tin_Thuoc_Duoi_Dang_Bang(THUOC thuoc)
{
	cout << "|" << setw(9) << left << thuoc.Ma_Thuoc;
	cout << "|" << setw(26) << left << thuoc.Ten_Thuoc;
	cout << "|" << setw(20) << left << thuoc.Trieu_Chung;
	cout << "|" << setw(10) << left << thuoc.So_Luong;
	cout << "|" << setw(7)  << thuoc.Gia_Thuoc;
	cout << setw(4) <<right<< "VND  |";
}

void Xuat_Danh_Sach_Thuoc(LIST list)
{
	cout << "\t|=======================================================================================|";
	printf("\n\t|%-5s|%-9s|%-25s |%-20s|%-10s|%-12s|\n","STT","Ma Thuoc", "Loai Thuoc", "Trieu Chung", "So Luong", "Gia thuoc");
	cout << "\t|=======================================================================================|\n";
	int i = 1;
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		cout << "\t|" << setw(5) << left << i;
		Xuat_Thong_Tin_Thuoc_Duoi_Dang_Bang(k->data1);
		cout << "\n\t|---------------------------------------------------------------------------------------|\n";
		i++;
	}
}

void Nhap_Thong_Tin_Thuoc(THUOC & thuoc)
{
	cout << "Ma thuoc: ";
	cin >> thuoc.Ma_Thuoc;
	cout << "Ten thuoc: ";
	cin.ignore();
	getline(std::cin, thuoc.Ten_Thuoc);
	fflush(stdin);
	cout << "Trieu chung dung thuoc: ";
	getline(std::cin, thuoc.Trieu_Chung);
	cout << "So luong muon nhap kho: ";
	cin >> thuoc.So_Luong;
	cout << "Gia cua mot vien thuoc: ";
	cin >> thuoc.Gia_Thuoc;
}

void Them_So_Luong_Thuoc (LIST & list)
{
	string TenThuoc;
	int SL;
	cout << "Loai thuoc can nhap: ";
	cin.ignore();
	getline(std::cin, TenThuoc);
	cout << "So luong nhap: ";
	cin >> SL;
	int i = -1;
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char*)k->data1.Ten_Thuoc.c_str(), (char*)TenThuoc.c_str()) == 0)
		{
			k->data1.So_Luong += SL;
			i = 1;
		}
	}
	if (i == -1)
		cout << "Khong tim thay " << TenThuoc << " trong danh sach thuoc!!!\n";
	else
	{
		cout << "Da nhap thuoc vao kho thanh cong!!!\n";
	}
}

void Tim_Kiem_Thuoc_Theo_Ten(LIST list)
{
	string TenThuoc;
	cout << "Nhap ten loai thuoc can tim: ";
	cin.ignore();
	getline(std::cin, TenThuoc);
	int i = -1;
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char*)k->data1.Ten_Thuoc.c_str(), (char*)TenThuoc.c_str()) == 0)
		{
			Xuat_Thong_Tin_1_Loai_Thuoc(k->data1);
			i = 1;
		}
	}
	if (i == -1)
		cout << "Khong tim thay thuoc!!!\n";
}

void Tim_Kiem_Thuoc_Theo_Trieu_Chung(LIST list)
{
	string TenTrieuChung;
	cout << "Nhap ten trieu chung mac phai: ";
	cin.ignore();
	getline(std::cin, TenTrieuChung);
	int i = -1;
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char*)k->data1.Trieu_Chung.c_str(), (char*)TenTrieuChung.c_str()) == 0)
		{
			Xuat_Thong_Tin_1_Loai_Thuoc(k->data1);
			i = 1;
		}
	}
	if (i == -1)
		cout << "Khong tim thay thuoc ung voi trieu chung can tim!!!\n";
}

void Hoan_Vi_Thuoc(THUOC& x, THUOC& y)
{
	THUOC temp = x;
	x = y;
	y = temp;
}

void Sap_Xep_Danh_Sach_Theo_So_Luong_Thuoc(LIST& list)
{
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		for (NODE* h = k->pNext; h != NULL; h = h->pNext)
		{
			int Thuoc1 = k->data1.So_Luong;
			int Thuoc2 = h->data1.So_Luong;
			if (Thuoc1 > Thuoc2)
			{
				Hoan_Vi_Thuoc(k->data1, h->data1);
			}
		}
	}
	cout << "\tDa sap xep danh sach thuoc thanh cong!!!\n";
}

void Ghi_Thong_Tin_1_Loai_Thuoc(fstream & fileout, THUOC thuoc)
{
	fileout << thuoc.Gia_Thuoc << ";";
	fileout << thuoc.Ten_Thuoc << ";";
	fileout << thuoc.Trieu_Chung<< ";";
	fileout << thuoc.So_Luong << ";";
	fileout << thuoc.Gia_Thuoc;
}

void Ghi_Danh_Sach_Thuoc_Vao_File(fstream & fileout, LIST list)
{
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		Ghi_Thong_Tin_1_Loai_Thuoc(fileout, k->data1);
		if (k->pNext != NULL) fileout << endl;
	}
	fileout.close();
}

int Menu_Quan_Ly_Thuoc(LIST & list)
{
	system("cls");
	int key;
	THUOC thuoc;
	NODE* p;
	char LuaChon;
	do
	{
		cout << "	        QUAN LY DANH SACH THUOC\n";
		cout << "======================MENU====================\n";
		cout << "|| 1. Hien thi danh sach thuoc.             ||\n";
		cout << "|| 2. Nhap them thuoc moi.                  ||\n";
		cout << "|| 3. Tim kiem thuoc.                       ||\n";
		cout << "|| 4. Sap xep danh sach theo so luong thuoc ||\n";
		cout << "|| 0. Thoat                                 ||\n";
		cout << "======================END=====================\n";
		cout << "Nhap tuy chon: ";
		cin >> key;
		switch (key)
		{
		case 1:
			Xuat_Danh_Sach_Thuoc(list);
			Clear();
			break;
		case 2:
			cout << "    Ban muon them:";
			cout << "\n       A. Them mot loai thuoc moi.";
			cout << "\n       B. Them thuoc theo so luong.";
			cout << "\n    Nhap lua chon: ";
			cin >> LuaChon;
			switch (LuaChon)
			{
			case 'A':
			case 'a':
				cout << "\n";
				Nhap_Thong_Tin_Thuoc(thuoc);
				p = KhoiTaoNodeThuoc(thuoc);
				ThemCuoi(list, p);
				cout << "\nDa them thuoc moi vao kho thanh cong!!!\n";
				Clear();
				break;
			case 'B':
			case 'b':
				Them_So_Luong_Thuoc(list);
				Clear();
				break;
			default:
				cout << "Nhap sai chuc nang.\n";
				Clear();
				break;
			}
			break;
		case 3:
			cout << "    Ban muon tim kiem:";
			cout << "\n       A. Tim kiem theo ten thuoc.";
			cout << "\n       B. Tim kiem theo trieu chung benh mac phai.";
			cout << "\n    Nhap lua chon: ";
			cin >> LuaChon;
			switch (LuaChon)
			{
			case 'A':
			case 'a':
				cout << "\n";
				Tim_Kiem_Thuoc_Theo_Ten(list);
				Clear();
				break;
			case 'B':
			case 'b':
				cout << "\n";
				Tim_Kiem_Thuoc_Theo_Trieu_Chung(list);
				Clear();
				break;
			default:
				cout << "Nhap sai chuc nang!!!\n";
				Clear();
				break;
			}
			break;
		case 4:
			Sap_Xep_Danh_Sach_Theo_So_Luong_Thuoc(list);
			Clear();
			break;
		case 0:
			return 0;
		default:
			cout << "\tKhong co chuc nang nay!\n\tVui long chon chuc nang trong menu.";
			Clear();
			break;
		}
	} while (true);
}
//------------------------------------------------------------------------------------------------------------------------

void Doc_Ngay_Thang_Nam(fstream & filein, TIME & date)
{
	filein >> date.Ngay;
	filein.seekg(1, 1);
	filein >> date.Thang;
	filein.seekg(1, 1);
	filein >> date.Nam;
}

void Doc_Thong_Tin_1_Khach_Hang (fstream & filein, KHACH_HANG & kh)
{
	getline(filein, kh.name, ';');
	filein >> kh.year;
	filein.seekg(1, 1);
	getline(filein, kh.so_dien_thoai, ';');
	getline(filein, kh.dia_chi, ';');
	Doc_Ngay_Thang_Nam(filein, kh.ngay_mua);
	filein.seekg(1, 1);
	getline(filein, kh.ten_thuoc, ';');
	filein >> kh.so_lan;
	filein.seekg(1, 1);
	filein >> kh.gia_tien;
	string tam;
	getline(filein, tam);
}

void Doc_Danh_Sach_Khach_Hang(fstream & filein, LIST &l)
{

	while (!filein.eof())
	{
		KHACH_HANG khachhang;
		Doc_Thong_Tin_1_Khach_Hang (filein, khachhang);
		NODE* p = KhoiTaoNodeKhachHang(khachhang);
		ThemCuoi(l, p);
	}
}

void Xuat_Thong_Tin_1_Khach_Hang(KHACH_HANG kh)
{
	cout << "\tHo va ten     : " << kh.name << endl;
	cout << "\tNam sinh      : " << kh.year << endl;
	cout << "\tSo dien thoai : " << kh.so_dien_thoai << endl;
	cout << "\tDia chi       : " << kh.dia_chi << endl;
	cout << "\tNgay mua      : " << kh.ngay_mua.Ngay << "/" << kh.ngay_mua.Thang << "/" << kh.ngay_mua.Nam << endl;
	cout << "\tTen thuoc     : " << kh.ten_thuoc << endl;
	cout << "\tSo lieu       : " << kh.so_lan << endl;
	cout << "\tTong tien     : " << kh.gia_tien << endl;
}

void Xuat_Thong_Tin_Khach_Hang_Duoi_Dang_Bang(NODE* p)
{
	cout << "|" << setw(24) << left << p->data2.name;
	cout << "|" << setw(8) << left << p->data2.year;
	cout << "|" << setw(15) << left << p->data2.so_dien_thoai;
	cout << "|" << setw(25) << left << p->data2.dia_chi;
	cout << "|" << p->data2.ngay_mua.Ngay << "/" << p->data2.ngay_mua.Thang << "/" << p->data2.ngay_mua.Nam << " ";
	cout << "|" << setw(25) << left << p->data2.ten_thuoc;
	cout << "|" << setw(7) << left << p->data2.so_lan;
	cout << "|" << setw(10) << left << p->data2.gia_tien << "|";
}

void Xuat_Danh_Sach_Khach_hang(LIST list)
{
	NODE* k = list.pHead;
	if (k != NULL)
	{
		cout << "    |==========================================================DANH SACH KHACH HANG==========================================================|";
		printf("\n    |%-3s|%-24s|%-8s|%-15s|%-25s|%-11s|%-25s|%-7s|%-10s|\n", "STT", "         Ho_Ten", "Nam Sinh", " So Dien Thoai", "         Dia Chi", " Ngay Mua","         Ten Thuoc","So Lieu","Tien Thuoc");
		cout << "    |========================================================================================================================================|\n";
		int i = 1;
		for (NODE* p = list.pHead; p != NULL; p = p->pNext)
		{
			cout << "    |" << setw(3) << left << i;
			Xuat_Thong_Tin_Khach_Hang_Duoi_Dang_Bang(p);
			cout << "\n    |----------------------------------------------------------------------------------------------------------------------------------------|\n";
			i++;
		}
	}
	else
		cout << "\tDanh sach khach hang trong !!" << endl;
}

void Xoa_Khach_Hang (LIST & l)
{
	string sdt;
	cout << "Nhap so dien thoai can xoa: ";
	cin >> sdt;
	int i = 0;
	bool found = false;
	NODE* khXoa = NULL;
	NODE* khTruoc = NULL;
	NODE* p = l.pHead;
	while (p != NULL)
	{
		if (p->data2.so_dien_thoai == sdt)
		{
			found = true;
			if (i == 0)
			{
				khXoa = l.pHead;
				l.pHead = l.pHead->pNext;
				delete khXoa;
			}
			else
			{
				khXoa = p;
				khTruoc->pNext = khTruoc->pNext->pNext;
				delete khXoa;
			}
			break;
		}
		khTruoc = p;
		p = p->pNext;
		i++;
	}
	if (!found)
		cout << "Khong tim thay so dien thoai: " << sdt << endl;
	else
		cout << "Da xoa khach hang voi so dien thoai: " << sdt << endl;
}

void Tim_Kiem_Khach_Hang_Theo_Ten(LIST list)
{
	string TenKH;
	cout << "Nhap ten khach hang can tim: ";
	cin.ignore();
	getline(std::cin, TenKH);
	int i = -1;
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		string Ten = Chi_Lay_Ten(k->data2.name);
		if (_stricmp((char*)Ten.c_str(), (char*)TenKH.c_str()) == 0)
		{
			Xuat_Thong_Tin_1_Khach_Hang(k->data2);
			cout << endl;
			i = 1;
		}
	}
	if (i == -1)
		cout << "Khong tim thay khach hang!!!\n";
}

void Tim_Kiem_Khach_Hang_Theo_SDT(LIST list)
{
	string SDT;
	cout << "Nhap so dien thoai can tim: ";
	cin.ignore();
	getline(std::cin, SDT);
	int i = -1;
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		if (_stricmp((char*)k->data2.so_dien_thoai.c_str(), (char*)SDT.c_str()) == 0)
		{
			Xuat_Thong_Tin_1_Khach_Hang(k->data2);
			i = 1;
		}
	}
	if (i == -1)
		cout << "Khong tim thay khach hang!!!\n";
}

void Hoan_Vi_Khach(KHACH_HANG & x, KHACH_HANG & y)
{
	KHACH_HANG temp = x;
	x = y;
	y = temp;
}

void Sap_Xep_Theo_Ten_Khach_Hang (LIST & list)
{
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		for (NODE* h = k->pNext; h != NULL; h = h->pNext)
		{
			string Ten1 = Chi_Lay_Ten(k->data2.name);
			string Ten2 = Chi_Lay_Ten(h->data2.name);
			if (_stricmp((char*)Ten1.c_str(), (char*)Ten2.c_str()) > 0)
			{
				Hoan_Vi_Khach(k->data2, h->data2);
			}
		}
	}
	cout << "\tDa sap xep danh sach khach hang thanh cong!!!\n";
}

void Ghi_Thong_Tin_1_Khach_Hang (fstream & fileout, KHACH_HANG kh)
{
	fileout << kh.name << ";";
	fileout << kh.year << ";";
	fileout << kh.so_dien_thoai << ";";
	fileout << kh.dia_chi;
	fileout << kh.ngay_mua.Ngay << "/" << kh.ngay_mua.Thang << "/" << kh.ngay_mua.Nam;
	fileout << kh.ten_thuoc << ";";
	fileout << kh.so_lan << ";";
	fileout << kh.gia_tien;
}

void Ghi_Danh_Sach_Khach_Hang_Vao_File(fstream & fileout, LIST list)
{
	for (NODE* k = list.pHead; k != NULL; k = k->pNext)
	{
		Ghi_Thong_Tin_1_Khach_Hang(fileout, k->data2);
		if (k->pNext != NULL) fileout << endl;
	}
	fileout.close();
}

int Menu_Quan_Danh_Sach_Khach_Hang(LIST & list)
{
	system("cls");
	int key;
	char LuaChon;
	do
	{
		cout << "           QUAN LY DANH SACH KHACH HANG\n";
		cout << "========================MENU=====================\n";
		cout << "|| 1. Hien thi danh sach danh sach khach hang.  ||\n";
		cout << "|| 2. Xoa khach hang theo SDT.                  ||\n";
		cout << "|| 3. Tim khach hang.                           ||\n";
		cout << "|| 4. Sap xep danh sach khach hang.             ||\n";
		cout << "|| 0. Thoat chuong trinh                        ||\n";
		cout << "========================END======================\n";
		cout << "Nhap lua chon: ";
		cin >> key;
		switch (key)
		{
		case 1:
			Xuat_Danh_Sach_Khach_hang(list);
			Clear();
			break;
		case 2:
			Xoa_Khach_Hang(list);
			Clear();
			break;
		case 3:
			cout << "    Ban muon tim kiem:";
			cout << "\n       A. Tim kiem theo ten cua khach hang.";
			cout << "\n       B. Tim kiem theo SDT cua khach hang.";
			cout << "\n    Nhap lua chon: ";
			cin >> LuaChon;
			switch (LuaChon)
			{
			case 'A':
			case 'a':
				cout << "\n";
				Tim_Kiem_Khach_Hang_Theo_Ten(list);
				Clear();
				break;
			case 'B':
			case 'b':
				cout << "\n";
				Tim_Kiem_Khach_Hang_Theo_SDT(list);
				Clear();
				break;
			default:
				cout << "Nhap sai chuc nang!!!\n";
				Clear();
				break;
			}
			break;
		case 4:
			Sap_Xep_Theo_Ten_Khach_Hang(list);
			Clear();
			break;
		case 0:
			return 0;
		default:
			cout << "\tKhong co chuc nang nay!\n\tVui long chon chuc nang trong menu.";
			Clear();
			break;
		}
	} while (true);
}

int main()
{
	LIST listthuoc,listkhach;
	NODE* p;

	KhoiTaoDanhSach(listthuoc);
	KhoiTaoDanhSach(listkhach);

	fstream file_thuoc;
	fstream file_khach;

	isEmpty(listthuoc);
	isEmpty(listkhach);

	file_thuoc.open("DANHSACHTHUOC.txt", ios::in | ios::out);
	file_khach.open("DANHSACHKHACH.txt", ios::in | ios::out);

	Doc_Danh_Sach_Thuoc(file_thuoc, listthuoc);
	Doc_Danh_Sach_Khach_Hang(file_khach, listkhach);
	
	int Lua_Chon_Chinh;
	do
	{
		cout << "       CHUONG TRINH QUAN LY TIEM THUOC \n";
		cout << "====================MENU====================\n";
		cout << "|| 1. Quan ly danh sach thuoc              ||\n";
		cout << "|| 2. Quan ly danh khach hang              ||\n";
		cout << "|| 3. Ban thuoc                            ||\n";
		cout << "|| 0. Thoat                                ||\n";
		cout << "=====================END====================\n";
		cout << "Nhap tuy chon: ";
		cin >> Lua_Chon_Chinh;
		switch (Lua_Chon_Chinh)
		{
		case 1:
			Menu_Quan_Ly_Thuoc(listthuoc);
			file_thuoc.open("DANHSACHTHUOC.txt", ios::out);
			Ghi_Danh_Sach_Thuoc_Vao_File(file_thuoc, listthuoc);
			Clear();
			break;
		case 2:
			Menu_Quan_Danh_Sach_Khach_Hang(listkhach);
			file_khach.open("DANHSACHKHACH.txt", ios::out);
			Ghi_Danh_Sach_Khach_Hang_Vao_File(file_khach, listkhach);
			Clear();
			break;
		case 3:
			break;
		case 0:
			return 0;
		default:
			cout << "\tKhong co chuc nang nay!\n\tVui long chon chuc nang trong menu.";
			Clear();
			break;
		}
	} while (true);
	file_thuoc.close();
	file_khach.close();
}



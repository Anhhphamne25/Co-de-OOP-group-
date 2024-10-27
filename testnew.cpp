#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Lớp cơ sở Nguoi
class Nguoi
{
protected:
    string maso;
    float luong;

private:
    string hoten;

public:
    void nhap()
    {
        cout << endl
             << "Nhap ma so(bc:bienche / hd:hopdong): ";
        cin >> maso;
        cout << endl
             << "Nhap ho ten: ";
        cin.ignore();
        getline(cin, hoten);
    }

    void in()
    {
        cout << endl
             << "Ma so: " << maso;
        cout << endl
             << "Ho ten: " << hoten;
        cout << endl
             << "Luong: " << luong;
    }
};

// Lớp kế thừa Bienche
class Bienche : virtual public Nguoi
{
private:
    double hsl;
    double pccv;

public:
    void nhap()
    {
        cout << endl
             << "Nhap he so luong(2.34,2.67,3,3.33,...): ";
        cin >> hsl;
        cout << endl
             << "Nhap tien phu cap chuc vu: ";
        cin >> pccv;
        luong = hsl * 2400000 + pccv;
    }
};

// Lớp kế thừa Hopdong
class Hopdong : virtual public Nguoi
{
private:
    float tcld, hsvg;
    int songaycong;

public:
    void nhap()
    {
        cout << endl
             << "Nhap tien cong lao dong: ";
        cin >> tcld;
        cout << endl
             << "Nhap so ngay lam viec: ";
        cin >> songaycong;
        cout << endl
             << "Nhap he so vuot gio: ";
        cin >> hsvg;
        luong = songaycong <= 26 ? songaycong * tcld : (songaycong + (songaycong - 26) * hsvg) * tcld;
    }
};


class NHANVIEN : public Bienche, public Hopdong
{
    static int tsnv;
    static float tsl;

public:
    NHANVIEN()
    {
        tsnv++;
    }
    ~NHANVIEN()
    {
        tsnv--;
        tsl -= luong;
    }
    void nhap()
    {
        Nguoi::nhap();
        if (maso[0] == 'b')
            Bienche::nhap();
        else
            Hopdong::nhap();
        tsl += luong;
    }
    static void ints()
    {
        cout << endl
             << "Tong so nhan vien: " << tsnv << endl
             << "Tong so luong: " << tsl;
    }
    NHANVIEN *next; // móc
};
int NHANVIEN::tsnv = 0;
float NHANVIEN::tsl = 0.0;
// Chương trình minh họa
int main()
{
    NHANVIEN *dau = NULL, *cuoi = NULL, *node = NULL;
    char tiep = 'c';
    while (tiep == 'c')
    {
        node = new NHANVIEN;
        node->nhap();
        node->next = NULL;
        if (dau == NULL)
        {
            dau = node;
            cuoi = node;
        }
        else
        {
            cuoi->next = node;
            cuoi = node;
        }
        cout << endl
             << "Nhap c de nhap tiep: ";
        cin >> tiep;
    }
    NHANVIEN *i = dau;
    while (i != NULL)
    {
        i->in();
        i = i->next;
    }
    NHANVIEN::ints();
    /*
        Nhanvien *nv;
        int n;
        cout << endl
             << "Nhap so luong nhan vien: ";
        cin >> n;
        nv = new Nhanvien[n];
        for (int i = 0; i < n; i++)
        {
            nv[i].nhap();
        }
        cout << endl
             << "Danh sach nhan vien vua nhap: ";
        for (int i = 0; i < n; i++)
        {
            nv[i].in();
        }*/
}

/*
Bienche *b;
int n;
cout<<endl<<"Nhap so luong bien che: ";cin>>n;
b= new Bienche[n];
for (int i=0;i<n;i++){
    b[i].Nguoi::nhap();
    b[i].nhap();
}
     cout <<endl<<"Danh sach bien che vua nhap:\n ";
     for (int i=0;i<n;i++){
        b[i].in();
     }
Hopdong*d;
int m;
cout<<endl<<"Nhap so luong hop dong: "; cin>>m;
d=new Hopdong[m];
for (int i=0;i<m;i++){
    d[i].Nguoi::nhap();
    d[i].nhap();

}
cout<<endl<<"Danh sach hop dong vua nhap: ";
for (int i=0;i<m;i++){
    d[i].in();
}
return 0;
*/
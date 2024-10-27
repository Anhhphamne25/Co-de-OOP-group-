#include<bits/stdc++.h>
using namespace std;

//Khai báo trước lớp phòng ban
class PHONGBAN {};

//lớp cơ sở người
class NGUOI{
    private:
        string hoten;

    protected:
        int sndl;
        string ID;
        double luong;

    public:
        void nhap(){
            cout<<endl<<"--->Nhập mã nhân viên: ";
            cin>>ID;
            cout<<endl<<"--->Nhập tên nhân viên: ";
            cin.ignore();
            getline(cin, hoten);
            cout<<endl<<"-->Nhập số ngày đi làm: ";
            cin>>sndl;
        }

        int laysndl() {
            return sndl;
        }
        
};

class CHUCVU: virtual public NGUOI {
    private:
        float hsl;//hệ số lương
        float pc;//phụ cấp
        string Cv;//chức vụ

    public:
        void nhap(){
            cout<<endl<<"-->Nhập chức vụ: ";
            cin>>Cv;
            cin.ignore();
            getline(cin, Cv);
            cout<<endl<<"-->Nhập hệ số lương: ";
            cin>>hsl;
            cout<<endl<<"-->Nhập Phụ cấp chức vụ: ";
            cin>>pc;
        }

        float laypc(){
            return pc;
        }

        float layhsl(){
            return hsl;
        }

        string layCv(){
            return Cv;
        }
};

class HOPDONG: virtual public NGUOI {
    private:
        double lcb;//lương cơ bản
        int snc;//số ngày công
        float hsvn; //hệ số vượt ngày
    public:
        void nhap(){
            cout<<endl<<"-->Nhập lương cơ bản: ";
            cin>>lcb;
            cout<<endl<<"-->Nhập số ngày công thỏa thuận: ";
            cin>>snc;
            cout<<endl<<"-->Nhập hệ số lương khi làm vượt ngày: ";
            cin>>hsvn;
        }

        double laylcb(){
            return lcb;
        }

        int laysnc(){
            return snc;
        }

        float layhsvn(){
            return hsvn;
        }
};

// Lớp PHONGBAN
class PHONGBAN {
private:
    string tenPhong;
    string maPhong;
    string truongPhong;
    vector<NHANVIEN*> danhSachNhanVien;

public:
    void nhap();

    void themNhanVien(NHANVIEN* nv) {
        danhSachNhanVien.push_back(nv);
    }

    void hienThiDanhSach() const {
        cout << "Danh sach nhan vien trong " << tenPhong << ":\n";
        for (const auto& nv : danhSachNhanVien) {
        }
    }

    string getTenPhong() const {
        return tenPhong;
    }
};



class RATING {

};



class NHANVIEN: public CHUCVU, public HOPDONG {
    static int slnv; //số lượng nhân viên
    static double tsl; //tổng số lương
    public:
        NHANVIEN() {
        slnv++;
        }

        ~NHANVIEN() {
        slnv--;
        tsl -= luong;
        }

        void tinhluong(){
            luong = laysndl() <= laysnc() ? (laylcb()*layhsl()) : ((laysndl()-laysnc())*laylcb() + laylcb()*layhsl()) ;
        }
        
        NHANVIEN* next; // Móc liên kết
};

int NHANVIEN::slnv = 0;
double NHANVIEN::tsl = 0.0;

int main(){
    mẹ mày béo lắm con ạ;
}

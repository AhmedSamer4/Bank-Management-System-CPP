#include <iostream> // للإدخال والإخراج عبر الشاشة (cin و cout)
#include <cstdlib>  // لتوليد الأرقام العشوائية (rand و srand)
#include <ctime>    // لاستخدام الوقت الحالي مع srand لتنويع الأرقام العشوائية
#include <vector>   // لاستخدام القائمة الديناميكية vector لتخزين العملاء
#include <string>   // للتعامل مع النصوص (string و getline)

using namespace std;

// فواصل شكلية لترتيب القوائم والبيانات على الشاشة
string lines = "    =========================================\n";
string line = "    ------------------------------------------------\n";

// ==========================================
// التعدادات (Enums): إعطاء أسماء واضحة لأرقام الخيارات
// ==========================================

// الخيارات الرئيسية في واجهة النظام العامة
enum operationsSystem
{
    adminLogin = 1, // الدخول كبوابة مدير
    clientATM = 2,  // الدخول كعميل للصراف الآلي
    logout = 3      // إغلاق البرنامج
};

// الخيارات المتاحة داخل لوحة تحكم المدير
enum operationsAdmin
{
    show = 1,   // عرض جميع العملاء
    add = 2,    // إضافة عميل جديد
    delet = 3,  // حذف عميل برقم الحساب
    update = 4, // تعديل بيانات عميل
    MM = 5,     // العودة للقائمة الرئيسية للنظام
};

// الخيارات المتاحة للعميل داخل الصراف الآلي (ATM)
enum operationsClient
{
    checkBalance = 1, // الاستعلام عن الرصيد
    deposit = 2,      // إيداع مبلغ مالي
    withdraw = 3,     // سحب مبلغ مالي
    Exit = 4          // تسجيل الخروج من الصراف الآلي
};

// الخيارات المتاحة للمدير عند تحديث بيانات العميل
enum updateDataClient
{
    all = 1,      // تحديث جميع البيانات
    name = 2,     // تحديث الاسم فقط
    password = 3, // تحديث كلمة المرور فقط
    balance = 4   // تحديث الرصيد فقط
};

// ==========================================
// الهياكل (Structs): تجميع بيانات كل كيان في قالب واحد
// ==========================================

// قالب بيانات العميل الواحد
struct infoClient
{
    string fullName;        // الاسم الكامل للعميل
    int numberAccount;      // رقم الحساب البنكي
    string passwordAccount; // كلمة مرور الحساب
    float balance;          // الرصيد الحالي
    bool isExit = false;    // علم للتحكم بالخروج من جلسة الصراف الآلي
};

// قالب بيانات المدير الافتراضية
struct infoAdmin
{
    string name = "Mr.Ahmed Samer"; // اسم المدير
    string password = "2006";       // كلمة مرور المدير
    bool Log = false;               // علم للتحكم بالعودة من لوحة المدير للقائمة الرئيسية
};

// قالب حالة تشغيل النظام العام
struct infoSystem
{
    bool lo = false; // علم للتحكم بإنهاء البرنامج بالكامل
};

// ==========================================
// دوال عمليات العميل (الصراف الآلي - ATM)
// ==========================================

// قراءة رقم العملية المطلوبة من العميل مع التحقق من أنه بين 1 و 4
operationsClient clientSelection()
{
    int selectionNumber;
    do
    {
        cout << "    Enter the transaction number you wish to perform: \n";
        cout << "    ";
        cin >> selectionNumber;
    } while (selectionNumber <= 0 || selectionNumber >= 5);

    return (operationsClient)selectionNumber;
}

// إرجاع الرصيد الحالي للعميل صاحب الفهرس i
float checkbalance(vector<infoClient> &info, int i)
{
    float chBa = info[i].balance;
    return chBa;
}

// تنفيذ عملية الإيداع ('+') أو السحب ('-') وتحديث الرصيد
bool depositWithdraw(vector<infoClient> &info, char type, int i)
{
    float deWi;
    bool isDeWi = false;

    if (type == '+') // حالة الإيداع
    {
        do
        {
            cout << "    Enter the deposit amount you wish to deposit into your account: ";
            cout << "    ";
            cin >> deWi;
        } while (deWi <= 0); // رفض المبالغ الصفرية أو السالبة

        info[i].balance = info[i].balance + deWi;
    }
    else // حالة السحب
    {
        do
        {
            cout << "    Enter the amount you want to withdraw from your account:  ";
            cout << "    ";
            cin >> deWi;
        } while (deWi <= 0);

        // التأكد من أن الرصيد كافٍ لتغطية مبلغ السحب
        if (deWi > info[i].balance)
        {
            cout << "    Error: You do not have enough funds to withdraw. Your account is $ " << info[i].balance << ".❌" << endl;
        }
        else
        {
            info[i].balance = info[i].balance - deWi;
        }
    }

    isDeWi = true;
    return isDeWi;
}

// توجيه العملية المختارة من العميل إلى الدالة المناسبة
void startOperationsClient(operationsClient num, vector<infoClient> &info, int i)
{
    float ChBa = checkbalance(info, i);

    switch (num)
    {
    case operationsClient::checkBalance:
        cout << "    Your balance is $" << ChBa << endl
             << endl;
        break;
    case operationsClient::deposit:
        depositWithdraw(info, '+', i);
        cout << endl
             << endl;
        break;
    case operationsClient::withdraw:
        depositWithdraw(info, '-', i);
        cout << endl
             << endl;
        break;
    case operationsClient::Exit:
        info[i].isExit = true; // طلب الخروج من حلقة الصراف الآلي
        break;
    }
}

// عرض قائمة خيارات الصراف الآلي للعميل
void mainClient()
{
    cout << lines << "                  ATM Main Menu                  \n"
         << lines
         << "    [1] Check Balance (الاستعلام عن الرصيد)\n"
         << "    [2] Deposit (إيداع مبلغ مالي)\n"
         << "    [3] Withdraw (سحب مبلغ مالي)\n"
         << "    [4] Logout / Exit (تسجيل الخروج)\n"
         << lines
         << "    Choose what do you want to do? [1 to 4]: \n";
}

// الحلقة الرئيسية لجلسة العميل حتى يختار تسجيل الخروج
void bodyClient(vector<infoClient> &info, int i)
{
    bool isLoguotOnClient;
    do
    {
        mainClient();
        operationsClient selectedClient = clientSelection();
        startOperationsClient(selectedClient, info, i);
        isLoguotOnClient = info[i].isExit;
    } while (!isLoguotOnClient);

    info[i].isExit = false; // إعادة ضبط العلم لاستخدامه في جلسة لاحقة
}

// ==========================================
// دوال تسجيل الدخول والتحقق
// ==========================================

// التحقق من اسم وكلمة مرور المدير مع إتاحة 3 محاولات كحد أقصى
bool loginAdmin(string password, string name)
{
    bool isLogin;
    string accNum;
    string accNam;
    int round = 0; // عداد المحاولات الخاطئة

    do
    {
        cin.ignore(1000, '\n'); // تنظيف مخزن الإدخال قبل قراءة الاسم بـ getline
        cout << "    Enter the admin's name: " << endl;
        cout << "    ";
        getline(cin, accNam);

        cout << "    Enter the admin password: " << endl;
        cout << "    ";
        cin >> accNum;

        if (accNum == password && accNam == name)
        {
            isLogin = true; // نجاح الدخول
        }
        else
        {
            isLogin = false;
            round++;
            cout << "    The entered data is incorrect, please verify it ❌\n";
            cout << "    You have " << (3 - round) << " attempts left out of 3.\n\n";
        }
    } while (!isLogin && round < 3);

    return isLogin;
}

// التحقق من حساب العميل وكلمة مروره وفتح الصراف الآلي عند النجاح
void loginClient(vector<infoClient> &client)
{
    bool isTrue = false;
    int accNum;
    string accPass;
    int round = 0; // عداد المحاولات
    int index;     // حفظ موقع العميل داخل الـ vector

    do
    {
        cout << "    Enter account number: " << endl;
        cout << "    ";
        cin >> accNum;

        cout << "    Enter your password:  " << endl;
        cout << "    ";
        cin >> accPass;

        // البحث عن عميل يطابق رقم الحساب وكلمة المرور
        for (int i = 0; i < client.size(); i++)
        {
            if (client[i].numberAccount == accNum && client[i].passwordAccount == accPass)
            {
                index = i;
                isTrue = true;
                break;
            }
            else
            {
                isTrue = false;
            }
        }

        if (isTrue)
        {
            cout << "    ✅" << endl;
            bodyClient(client, index); // الدخول لواجهة الصراف الآلي الخاصة بهذا العميل
        }
        else
        {
            round++;
            cout << "    The entered data is incorrect, please verify it ❌\n";
            cout << "    You have " << (3 - round) << " attempts left out of 3.\n\n";
        }

    } while (!isTrue && round < 3);
}

// ==========================================
// دوال عمليات المدير (CRUD وإدارة العملاء)
// ==========================================

// إضافة عميل جديد وتوليد رقم حساب عشوائي له وإضافته للـ vector
void addClient(vector<infoClient> &client)
{
    cin.ignore(1000, '\n'); // تفريغ أي سطر متبقٍ في المخزن المؤقت
    infoClient tempClient;

    cout << "    Enter client name: " << endl;
    cout << "    ";
    getline(cin, tempClient.fullName);

    cout << "    Enter your password: " << endl;
    cout << "    ";
    cin >> tempClient.passwordAccount;

    tempClient.numberAccount = (rand() % 900000) + 100000; // رقم حساب من 6 أرقام
    tempClient.balance = 0.0;
    tempClient.isExit = false;

    client.push_back(tempClient); // حفظ العميل في القائمة
    cout << "    A new client has been successfully added. ✅" << endl
         << endl;
}

// عرض بيانات جميع العملاء المسجلين في النظام
void showClients(vector<infoClient> &client)
{
    if (client.empty())
    {
        cout << "        Sorry, there are no clients. Please add clients from the main menu." << endl;
    }
    else
    {
        for (int i = 0; i <= client.size() - 1; i++)
        {
            cout << line;
            cout << "    Name:- " << client[i].fullName << endl;
            cout << "    Account number:- " << client[i].numberAccount << endl;
            cout << "    password:- " << client[i].passwordAccount << endl;
            cout << "    Balance:- " << client[i].balance << endl;
            cout << line;
        }
    }
}

// حذف عميل من الـ vector بالبحث عن رقم حسابه
void deleteClients(vector<infoClient> &client)
{
    if (!client.empty())
    {
        int numClient;
        bool found = false; // لتتبع هل تم العثور على الحساب وحذفه

        cout << "    Enter the bank account number to delete the customer: " << endl;
        cout << "    ";
        cin >> numClient;

        for (int i = 0; i < client.size(); i++)
        {
            if (client[i].numberAccount == numClient)
            {
                client.erase(client.begin() + i); // حذف العنصر من الموضع i
                cout << "    The client has been successfully deleted. ✅" << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "    No client with this account number❌" << endl;
        }
    }
    else
    {
        cout << "    Sorry, there are no client yet, so one needs to be removed.❌" << endl;
    }
}

// قراءة الحقل المراد تحديثه (من 1 إلى 4)
updateDataClient selectionUpdateData()
{
    int choseing;
    do
    {
        cout << "    Choose what you want to update: " << endl;
        cin >> choseing;
    } while (choseing < 1 || choseing > 4);

    return (updateDataClient)choseing;
}

// البحث عن فهرس (index) العميل المطلوب تعديله عبر رقم الحساب
int numberAccountClient(vector<infoClient> &client)
{
    bool isTrue = true;
    if (!client.empty())
    {
        int numClient;
        do
        {
            cout << "    Enter the bank account number to update the client: " << endl;
            cout << "    ";
            cin >> numClient;

            for (int i = 0; i < client.size(); i++)
            {
                if (client[i].numberAccount == numClient)
                {
                    isTrue = false;
                    return i; // إرجاع موقع العميل في الـ vector
                }
            }
            cout << "    No client with this account number❌" << endl;

        } while (isTrue);
    }
    else
    {
        cout << "    Sorry, there are no client yet, so one needs to be removed.❌" << endl;
        return -1; // إشارة لعدم وجود عملاء للتعديل
    }
}

// تحديث اسم العميل مع منع إدخال نفس الاسم القديم
void updateName(vector<infoClient> &client, int i)
{
    cin.ignore(1000, '\n');
    string name;
    do
    {
        cout << "    Enter the new name: " << endl;
        getline(cin, name);
    } while (name == client[i].fullName);

    client[i].fullName = name;
    cout << "    The name has been successfully changed. ✅" << endl;
}

// تحديث كلمة مرور العميل مع منع تكرار كلمة المرور الحالية
void updatePassword(vector<infoClient> &client, int i)
{
    string password;
    do
    {
        cout << "    Enter your new password: " << endl;
        cin >> password;
    } while (password == client[i].passwordAccount);

    client[i].passwordAccount = password;
    cout << "    Password changed successfully ✅" << endl;
}

// تحديث رصيد العميل مع منع إدخال نفس الرصيد الحالي
void updateBalance(vector<infoClient> &client, int i)
{
    float balance;
    do
    {
        cout << "    Enter the new balance number: " << endl;
        cin >> balance;
    } while (balance == client[i].balance);

    client[i].balance = balance;
    cout << "    Balance updated successfully ✅" << endl;
}

// تحديث جميع بيانات العميل (الاسم، كلمة المرور، الرصيد) دفعة واحدة
void updateAll(vector<infoClient> &client, int i)
{
    updateName(client, i);
    updatePassword(client, i);
    updateBalance(client, i);
    cout << "    All data has been successfully updated. ✅" << endl;
}

// إدارة عملية تحديث بيانات العميل حسب اختيار المدير
void updateClients(vector<infoClient> &client)
{
    cout << "    [1] Update all data (تحديث جميع البيانات)" << endl;
    cout << "    [2] Name update (تحديث الأسم)" << endl;
    cout << "    [3] Update password (تحديث كلمة المرور)" << endl;
    cout << "    [4] Balance Update (تحديث الرصيد)" << endl;

    int choseing = selectionUpdateData();
    int i = numberAccountClient(client);

    if (i != -1)
    {
        switch (choseing)
        {
        case updateDataClient::all:
            updateAll(client, i);
            break;
        case updateDataClient::name:
            updateName(client, i);
            break;
        case updateDataClient::password:
            updatePassword(client, i);
            break;
        case updateDataClient::balance:
            updateBalance(client, i);
            break;
        }
    }
}

// توجيه أمر المدير إلى الدالة المسؤولة عنه
void startOperationsAdmin(operationsAdmin num, vector<infoClient> &client, infoAdmin &info)
{
    switch (num)
    {
    case operationsAdmin::show:
        showClients(client);
        break;
    case operationsAdmin::add:
        addClient(client);
        break;
    case operationsAdmin::delet:
        deleteClients(client);
        break;
    case operationsAdmin::update:
        updateClients(client);
        break;
    case operationsAdmin::MM:
        info.Log = true; // العودة للشاشة الرئيسية للنظام
        break;
    }
}

// قراءة اختيار المدير من قائمة الإدارة (من 1 إلى 5)
operationsAdmin selectedAdmin()
{
    int admin;
    do
    {
        cout << "    Enter the transaction number you wish to perform: \n";
        cout << "    ";
        cin >> admin;
    } while (admin <= 0 || admin >= 6);

    return (operationsAdmin)admin;
}

// عرض قائمة لوحة تحكم المدير
void mainAdmin()
{
    cout << lines;
    cout << "               WELCOME TO ADMIN SYSTEM         " << endl;
    cout << lines;
    cout << "    [1] Show Client List (أظهار عملاء البنك)" << endl;
    cout << "    [2] Add New Client (أضافة عميل جديد)" << endl;
    cout << "    [3] Delete Client (حذف عميل)" << endl;
    cout << "    [4] Update Client (تعديل بيانات عميل)" << endl;
    cout << "    [5] Main Menu (الشاشة الرئيسية)" << endl;
    cout << "    Choose your portal [1-5]:" << endl;
}

// الحلقة الرئيسية للوحة تحكم المدير حتى يختار العودة للقائمة الرئيسية
void bodyAdmin(vector<infoClient> &client, infoAdmin &info)
{
    bool isLoguotOnAdmin;
    do
    {
        mainAdmin();
        operationsAdmin selected = selectedAdmin();
        startOperationsAdmin(selected, client, info);
        isLoguotOnAdmin = info.Log;
    } while (!isLoguotOnAdmin);

    info.Log = false; // إعادة ضبط العلم للدخول المستقبلي
}

// ==========================================
// دوال النظام الرئيسية ونقطة البداية (main)
// ==========================================

// قراءة اختيار البوابة الرئيسية (من 1 إلى 3)
operationsSystem systemSelection()
{
    int system;
    do
    {
        cout << "    Enter the transaction number you wish to perform: \n";
        cout << "    ";
        cin >> system;
    } while (system <= 0 || system >= 4);

    return (operationsSystem)system;
}

// تنفيذ الخيار المختار من القائمة الرئيسية (مدير، صراف آلي، خروج)
void startOperationsSystem(operationsSystem num, infoAdmin infoA, vector<infoClient> &client, infoSystem &infoS)
{
    bool scsLoA;
    switch (num)
    {
    case operationsSystem::adminLogin:
        scsLoA = loginAdmin(infoA.password, infoA.name);
        if (scsLoA)
        {
            cout << "    ✅" << endl;
            bodyAdmin(client, infoA);
        }
        else
        {
            cout << "    ❌" << endl;
        }
        break;

    case operationsSystem::clientATM:
        if (!client.empty())
        {
            loginClient(client);
        }
        else
        {
            cout << "    Sorry, there are no client on the system. ❌" << endl;
        }
        break;

    case operationsSystem::logout:
        infoS.lo = true; // إنهاء حلقة النظام الرئيسية
        break;
    }
}

// عرض القائمة الرئيسية للنظام
void mainMenu()
{
    cout << lines;
    cout << "               WELCOME TO BANK SYSTEM         " << endl;
    cout << lines << endl;
    cout << "    [1] Admin Login (دخول المدير / الإدارة)" << endl;
    cout << "    [2] Client ATM (دخول العميل للصراف الآلي)" << endl;
    cout << "    [3] Exit (خروج)" << endl;
    cout << "    Choose your portal [1-3]:" << endl;
}

// حلقة تشغيل النظام المستمرة حتى يختار المستخدم الخروج
void bodySystem(infoAdmin infoA, vector<infoClient> &client, infoSystem &infoS)
{
    int isLo;
    do
    {
        mainMenu();
        operationsSystem selected = systemSelection();
        startOperationsSystem(selected, infoA, client, infoS);
        isLo = infoS.lo;
    } while (!isLo);

    cout << "    Successful exit ✅" << endl;
}

// نقطة انطلاق البرنامج
int main()
{
    srand(time(0));          // تهيئة مولد الأرقام العشوائية بناءً على الوقت الحالي
    vector<infoClient> clients; // قائمة العملاء في الذاكرة
    infoAdmin infoA;            // بيانات المدير
    infoSystem infoS;           // حالة النظام

    bodySystem(infoA, clients, infoS); // تشغيل النظام
    return 0;
}

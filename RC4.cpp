#include<iostream>
#include<string>
#include<bitset>
#include<vector>
#include<cmath>
using namespace std;

int N = 1000000;
bool resultfrequency;


void Runs_Test(int binaryaraay[], int n)
{
    float counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (binaryaraay[i] == 1)
            counter++;
    }
    float pi;
    pi = counter / n;
    float t;
    t = 2 / sqrt(n);
    if (resultfrequency==true)
    {

        int v = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (binaryaraay[i] != binaryaraay[i + 1])
            {
                v++;
            }
        }
        v++;
        double p_value;
        p_value = erfc(abs((v - (2 * n * pi * (1 - pi)))) / (2 * sqrt(2 * n) * pi * (1 - pi)));
        cout <<"p value : "<< p_value << endl;

        if (p_value >= 0.01)

            cout << "success\n";
        else
            cout << " fail "<<endl ;


    }
    else
    {
        cout << " it did not pass the frequency test -> fail \n ";
    }

}



float Frequency(int binaryaraay[], int n)
{
    int		i;
    double	f, s_obs, p_value, sum;
    sum = 0.0;
    for (i = 0; i < n; i++)
        sum = sum + (2 * binaryaraay[i] - 1);
    s_obs = fabs(sum) / sqrt(n);
    f = s_obs / sqrt(2);
    p_value = erfc(f);
    return p_value;
}


int getMaxLength(int binaryaraay[], int n)
{
    int count = 0;
    int result = 0;

    for (int i = 0; i < n; i++)
    {
        if (binaryaraay[i] == 1)
            count = 0;
        else
        {
            count++;
            result = max(result, count);
        }
    }

    return result;
}

int main()
{
    cout << "Enter the number of keys(less than 256) : ";
    int n_Of_K;
    cin >> n_Of_K;
    int* key = new int[125000];
    for (int i = 0; i < n_Of_K; i++)
    {
        int x;
        cout << "enter key "<< i+1 <<" :";
        cin >> x;
        key[i] = x;
    }
   
    int s[256];
    int t[256];
    for (int i = 0; i < 256; i++)
    {
        s[i] = i;
        t[i] = key[i % (n_Of_K )];
    }

    int temp = 0;
    for (int i = 0; i < 256; i++)
    {
        temp = (temp + s[i] + t[i]) % 256;
        swap(s[i], s[temp]);
    }

    int i = 0;
    int j = 0;
    int c = 0;
    while (c < 125000)
    {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(s[i], s[j]);
       int temp1 = (s[i] + s[j]) % 256;
        key[c] = temp1;

        c++;
    }

    for (int i = 0; i < 125000; i++)
    {

        // cout << key[i]<<"  ";

    }


    int* binaryaraay = new int[1000000];
    bitset<8> bit1;
    int eight = 0;
    for (int i = 0; i < 125000; i++)
    {
        bit1 = key[i];
        for (int j = 0; j < 8; j++)
        {
            binaryaraay[j + eight] = bit1[j];
        }
        eight = eight + 8;
    }

    for (int j = 0; j < 1000000; j++)
    {

        //cout << binaryaraay[j];

    }
    int complete;
    do
    {
        cout << "Choose Test : " << endl;
        cout << "1. Frequency test" << endl;
        cout << "2. 0-1 test" << endl;
        cout << "3. 00 test" << endl;
        cout << "4. max num consecutive of 0 test " << endl;
        cout << "5. Run test" << endl;

        int choose;
        cin >> choose;
        switch (choose)
        {
        case 1:
        {
            float try1;

            try1 = Frequency(binaryaraay, N);
            cout << "p_value is : " << try1 << endl;
            if (try1 >= 0.01)
            {
                cout << "success" << endl;
                resultfrequency = true;
            }
            else
            {
                cout << "faild" << endl;
                resultfrequency = false;
            }
        }
        break;
        case 2:
        {
            int calc0 = 0, calc1 = 0;
            for (int i = 0; i < N; i++)
            {
                if (binaryaraay[i] == 0)
                    calc0++;

                else
                    calc1++;
            }
            cout << "number of 0 : " << calc0 << endl;
            cout << "number of 1 : " << calc1 << endl;
            int calc01;
            if (calc0 > calc1)
                calc01 = calc0 - calc1;
            else
                calc01 = calc1 - calc0;

            if (calc01 <= 10 * sqrt(N))
                cout << "success" << endl;
            else
                cout << "fail" << endl;
        }
        break;
        case 3:
        {
            int check00 = 0;
            int test00 = 0;
            for (int i = 1; i < N; i++)
            {
                if (binaryaraay[i] == 0 && binaryaraay[i - 1] == 0)
                    check00++;
            }
            cout << " nomber of 00 = " << check00 << endl;
            if ((check00 - N / 4) > 0)
                test00 = check00 - N / 4;
            else
                test00 = N / 4 - check00;

            if (test00 <= 10 * sqrt(N))
                cout << "success" << endl;
            else
                cout << "faild" << endl;

        }
        break;
        case 4:
        {
            int max_num_consecutive0;
            max_num_consecutive0 = getMaxLength(binaryaraay, N);
            cout << " number of consecutive 0 = " << max_num_consecutive0 << endl;
            if (max_num_consecutive0 <= log2(N))
                cout << "success" << endl;
            else
                cout << "faild" << endl;


        }
        break;
        case 5:
        {



            Runs_Test(binaryaraay, N);

             
        }
        break;
        default:
        {
            cout << "Wrong Choice .." << endl;
        }
        }
        cout << "want continue ??" << endl;
        cout << "1 .yes " << endl;

        cin >> complete;
    } while (complete == 1);

    system("pause");
    return 0;

}

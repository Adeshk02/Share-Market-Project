#include<stdio.h>
#include<string.h>
#define num_of_com 10 
#define num_of_days 10

typedef struct 
{
   char name[100] ;
   float Open ;  
   float High ;
   float Low ;
   float Close ;
   float Volume ;

}Stock;
    // FUNCTION FOR QUESTION 1;
void percentagechangeinstock (Stock S[num_of_com][num_of_days] , int start_date , int end_date){
    printf("Percentage change in prices from day %d to day %d are:\n",start_date,end_date);

    for(int i = 0 ; i < num_of_com ; i++){
        float  diff = S[i][end_date].Close - S[i][start_date].Close ;
        float change = (diff/S[i][end_date].Close)*100 ;
        printf("%s  ->  %f\n", S[i][start_date].name,change) ;
    }


}
    // FUNCTION FOR QUESTION 2;

void sortStockVolumeClose(Stock S[num_of_com][num_of_days], int day) {
    Stock temp;
    // Bubble sort to arrange stock data by volume and close price on a particular day
    for (int i = 0; i < num_of_com - 1; i++) {
        for (int j = 0; j < num_of_com - i - 1; j++) {
            // Sort based on volume
            if (S[j][day].Volume > S[j + 1][day].Volume) {
                temp = S[j][day];
                S[j][day] = S[j + 1][day];
                S[j + 1][day] = temp;
            } else if (S[j][day].Volume == S[j + 1][day].Volume) {
                // For equal volume, sort based on close price
                if (S[j][day].Close > S[j + 1][day].Close) {
                    temp = S[j][day];
                    S[j][day] = S[j + 1][day];
                    S[j + 1][day] = temp;
                }
            }
        }
    }
}

    // FUNCTION FOR QUESTION 3;
void profitloss (Stock S[num_of_com][num_of_days] , int buy_date , int sell_date){
    printf("Profit/Loss from buying date %d and selling date %d is:\n",buy_date,sell_date);
    for(int i = 0 ; i < num_of_com ; i++){
        float diff_High = S[i][sell_date].High - S[i][buy_date].High ;
        if(diff_High<0){
            diff_High = diff_High * (-1) ;
            printf("%s  ->  %f Loss\n", S[i][buy_date].name,diff_High) ;
        }
        else{
            printf("%s  ->  %f Profit\n", S[i][buy_date].name,diff_High) ;
        }
    }
}
    // FUNCTION FOR QUESTION 4;
void highestprofit (Stock S[num_of_com][num_of_days], int buy_date, int sell_date){
    int maxprofit = 0;
    char bestcomp[50];

    for (int i = 0; i < num_of_com; i++) {
        int profit = ((S[i][sell_date].Close - S[i][buy_date].Close) * 100) / S[i][buy_date].Close;

        if (profit > maxprofit) {
            maxprofit = profit;
            strcpy(bestcomp, S[i][buy_date].name);
        }
    }
    printf("Best Company: %s\n", bestcomp);
    printf("Maximum Profit: %d%%\n", maxprofit);
}

    // FUNCTION FOR QUESTION 5;
void lowestprofit(Stock S[num_of_com][num_of_days], int buy_date, int sell_date){
    int minprofit = 0;
    char worstcomp[50];

    for (int i = 0; i < num_of_com; i++) {
        int profit = ((S[i][sell_date].Close - S[i][buy_date].Close) * 100) / S[i][buy_date].Close;

        if (profit < minprofit) {
            minprofit = profit;
            strcpy(worstcomp, S[i][buy_date].name);
        }
    }
    printf("Worst Company: %s\n", worstcomp);
    printf("Minimum Profit: %d%%\n", minprofit);
}
 // FUNCTION FOR QUESTION 6;

void overallperformance(Stock S[num_of_com][num_of_days], int start_date, int end_date) {
    float overall_performance[num_of_com]; // Array to hold overall performance for each stock
    for (int i = 0; i < num_of_com; i++) {
        overall_performance[i] = 0; // Initialize overall performance to 0 for each stock
    }

    for (int i = 0; i < num_of_com; i++) {
        for (int j = start_date + 1; j <= end_date; j++) {
            float percentage_change = ((S[i][j].Close - S[i][j - 1].Close) / S[i][j - 1].Close) * 100;
            overall_performance[i] += (percentage_change * S[i][j].Volume);
        }
    }

    // Sort stocks based on their overall performance
    for (int i = 0; i < num_of_com - 1; i++) {
        for (int j = 0; j < num_of_com - i - 1; j++) {
            if (overall_performance[j] > overall_performance[j + 1]) {
                // Swap overall performance
                float temp = overall_performance[j];
                overall_performance[j] = overall_performance[j + 1];
                overall_performance[j + 1] = temp;

                // Swap Stocks (Assuming you want to re-order the array of stocks)
                Stock temp_stock[num_of_days];
                memcpy(temp_stock, S[j], sizeof(Stock));
                memcpy(S[j], S[j + 1], sizeof(Stock));
                memcpy(S[j + 1], temp_stock, sizeof(Stock));
            }
        }
    }

    // Print the stocks based on their overall performance
    printf("Stocks listed as per increasing overall performance:\n");
    for (int i = 0; i < num_of_com; i++) {
        printf("%s - Overall Performance: %.2f\n", S[i][0].name, overall_performance[i]);
    }
}

    // FUNCTION FOR QUESTION 7;
void averageofaverage(Stock S[num_of_com][num_of_days], int start_date, int end_date) {
    float total_weighted_sum = 0;
    float total_volume = 0;

    for (int i = 0; i < num_of_com; i++) {
        float weighted_sum = 0;
        float total_stock_volume = 0;

        for (int j = start_date; j <= end_date; j++) {
            weighted_sum += S[i][j].Close * S[i][j].Volume;
            total_stock_volume += S[i][j].Volume;
        }

        total_weighted_sum += weighted_sum;
        total_volume += total_stock_volume;
    }

    float average_value = total_weighted_sum / total_volume;

    printf("Average value of all stocks from start date %d to end date %d: %f\n", start_date, end_date, average_value);
}
   
int main(){
    
    Stock Company[num_of_com][num_of_days];


    for(int i = 0 ; i < num_of_days ; i++){
        strcpy(Company[0][i].name,"MICROSOFT") ;
        strcpy(Company[1][i].name,"APPLE") ;
        strcpy(Company[2][i].name,"ALPHABET") ;
        strcpy(Company[3][i].name,"AMAZON") ;
        strcpy(Company[4][i].name,"INTEL") ;
        strcpy(Company[5][i].name,"FACEBOOK") ;
        strcpy(Company[6][i].name,"GOOGLE") ;
        strcpy(Company[7][i].name,"TCS") ;
        strcpy(Company[8][i].name,"ALIBABA") ;
        strcpy(Company[9][i].name,"HCL") ;
    }
    
    //MICROSOFT 

    Company[0][9].Open = 1204.75 ;
    Company[0][8].Open = 1225.45 ;
    Company[0][7].Open = 1208.75 ;
    Company[0][6].Open = 1221.85 ;
    Company[0][5].Open = 1279.9  ;
    Company[0][4].Open = 1245.1  ;
    Company[0][3].Open = 1258    ;
    Company[0][2].Open = 1254.35 ;
    Company[0][1].Open = 1269    ;
    Company[0][0].Open = 1245.7  ;

    Company[0][9].High = 1247.7;
    Company[0][8].High = 1275.96;
    Company[0][7].High = 1235.7;
    Company[0][6].High = 1248.7;
    Company[0][5].High = 1291.55;
    Company[0][4].High = 1275.25;
    Company[0][3].High = 1259.75;
    Company[0][2].High =  1269.9;
    Company[0][1].High =  1267.3;
    Company[0][0].High =  1255.9;

    Company[0][9].Low = 1202.6;
    Company[0][8].Low = 1220.6;
    Company[0][7].Low = 1205.64;
    Company[0][6].Low = 1219.6;
    Company[0][5].Low = 1277;
    Company[0][4].Low = 1244.95;
    Company[0][3].Low = 1249;
    Company[0][2].Low = 1254.1 ;
    Company[0][1].Low = 1249.7; 
    Company[0][0].Low = 1232.75 ;

    Company[0][9].Close = 1289.11;
    Company[0][8].Close = 1274.17;
    Company[0][7].Close = 1275.45;
    Company[0][6].Close = 1270.1;
    Company[0][5].Close = 1270.4;
    Company[0][4].Close = 1270;
    Company[0][3].Close = 1250.05;
    Company[0][2].Close = 1250.9 ;
    Company[0][1].Close = 1240.95; 
    Company[0][0].Close = 1250.3 ;             

    Company[0][9].Volume = 209448078;      
    Company[0][8].Volume = 10472578;
    Company[0][7].Volume = 20145782;
    Company[0][6].Volume = 20926078;
    Company[0][5].Volume = 24241759;
    Company[0][4].Volume = 23868774;
    Company[0][3].Volume = 26912847;
    Company[0][2].Volume = 19361636;
    Company[0][1].Volume = 24455992; 
    Company[0][0].Volume = 28745915;                

    // APPLE

    Company[1][9].Open = 358.35 ;
    Company[1][8].Open = 317.35 ;
    Company[1][7].Open = 315.75 ;
    Company[1][6].Open = 317.35 ;
    Company[1][5].Open = 313  ;
    Company[1][4].Open = 307.85  ;
    Company[1][3].Open = 305    ;
    Company[1][2].Open = 302.55 ;
    Company[1][1].Open = 304.55  ;
    Company[1][0].Open = 288.25  ;

    Company[1][9].High = 308.75;
    Company[1][8].High = 389.75;
    Company[1][7].High = 320.85;
    Company[1][6].High = 319.75;
    Company[1][5].High = 318.35;
    Company[1][4].High = 313.65;
    Company[1][3].High = 310.85;
    Company[1][2].High = 309.1 ;
    Company[1][1].High = 305;
    Company[1][0].High = 303.9 ;

    Company[1][9].Low = 371.35;
    Company[1][8].Low = 378.14;
    Company[1][7].Low = 356.55;
    Company[1][6].Low = 315.25;
    Company[1][5].Low = 312.1;
    Company[1][4].Low = 306.55;
    Company[1][3].Low = 304.45;
    Company[1][2].Low = 301.9 ;
    Company[1][1].Low = 299.45; 
    Company[1][0].Low = 287.8 ;

    Company[1][9].Close = 378.95;
    Company[1][8].Close = 348.95;
    Company[1][7].Close = 325.95;
    Company[1][6].Close = 316.95;
    Company[1][5].Close = 317.4;
    Company[1][4].Close = 312;
    Company[1][3].Close = 307.95;
    Company[1][2].Close = 307.2 ;
    Company[1][1].Close = 301.85; 
    Company[1][0].Close = 303.25 ;             

    Company[1][9].Volume = 47258837;
    Company[1][8].Volume = 9892837;
    Company[1][7].Volume = 9662477;                
    Company[1][6].Volume = 9662837;
    Company[1][5].Volume = 7760527;
    Company[1][4].Volume = 10535107;
    Company[1][3].Volume = 9516879;
    Company[1][2].Volume = 15375295;
    Company[1][1].Volume = 12321154; 
    Company[1][0].Volume = 28745957;

    // ALPHABET

    Company[2][9].Open = 947.2 ;
    Company[2][8].Open = 955.2 ;
    Company[2][7].Open = 950.2 ;
    Company[2][6].Open = 949.2 ;
    Company[2][5].Open = 955.4  ;
    Company[2][4].Open = 948.5  ;
    Company[2][3].Open = 949.95    ;
    Company[2][2].Open = 952.85 ;
    Company[2][1].Open = 954.9    ;
    Company[2][0].Open = 940.4  ;

    Company[2][9].High = 978.85;
    Company[2][8].High = 985.65;
    Company[2][7].High = 957.75;
    Company[2][6].High = 950.65;
    Company[2][5].High = 960.95;
    Company[2][4].High = 954.85;
    Company[2][3].High = 957.4;
    Company[2][2].High = 960.1;
    Company[2][1].High = 962.05;
    Company[2][0].High = 957.5;

    Company[2][9].Low = 985.41;
    Company[2][8].Low = 999.1;
    Company[2][7].Low = 948.19;
    Company[2][6].Low = 939.1;
    Company[2][5].Low = 951.5;
    Company[2][4].Low = 946.15;
    Company[2][3].Low = 944.55;
    Company[2][2].Low = 948.4 ;
    Company[2][1].Low = 950.75; 
    Company[2][0].Low = 940.35 ;

    Company[2][9].Close = 975.75;
    Company[2][8].Close = 958.95;
    Company[2][7].Close = 947.45;
    Company[2][6].Close = 943.75;
    Company[2][5].Close = 953.9;
    Company[2][4].Close = 951.4;
    Company[2][3].Close = 951.3;
    Company[2][2].Close = 954.25 ;
    Company[2][1].Close = 953.1; 
    Company[2][0].Close = 951.2 ;             
                        
    Company[2][9].Volume = 19632852;
    Company[2][8].Volume = 18521478;
    Company[2][7].Volume = 11452078;
    Company[2][6].Volume = 12154782;
    Company[2][5].Volume = 7747527;
    Company[2][4].Volume = 5763024;
    Company[2][3].Volume = 6650442;
    Company[2][2].Volume = 7836818;
    Company[2][1].Volume = 12321154; 
    Company[2][0].Volume = 11452715;

    // AMAZON

    Company[3][9].Open = 2478 ;
    Company[3][8].Open = 2458 ;
    Company[3][7].Open = 2480 ;
    Company[3][6].Open = 2440 ;
    Company[3][5].Open = 2459.95 ;
    Company[3][4].Open = 2454.55  ;
    Company[3][3].Open = 2488    ;
    Company[3][2].Open = 2499 ;
    Company[3][1].Open = 2533    ;
    Company[3][0].Open = 2443  ;

    Company[3][9].High = 2741.85;
    Company[3][8].High = 2521.65;
    Company[3][7].High = 2475.95;
    Company[3][6].High = 2441.75;
    Company[3][5].High = 2462;
    Company[3][4].High = 2464.70;
    Company[3][3].High = 2495;
    Company[3][2].High =  2521.75;
    Company[3][1].High =  2538;
    Company[3][0].High =  2515.95;

    Company[3][9].Low = 2405.15;
    Company[3][8].Low = 2414.55;
    Company[3][7].Low = 2428.45;
    Company[3][6].Low = 2401.05;
    Company[3][5].Low = 2423.50;
    Company[3][4].Low = 2421.85;
    Company[3][3].Low = 2422.35;
    Company[3][2].Low = 2490.65;
    Company[3][1].Low = 2482.5; 
    Company[3][0].Low = 2443 ;

    Company[3][9].Close = 2485.35;
    Company[3][8].Close = 2446.85;
    Company[3][7].Close = 2425.75;
    Company[3][6].Close = 2406.35;
    Company[3][5].Close = 2428.40;
    Company[3][4].Close = 2429.35;
    Company[3][3].Close = 2454.55;
    Company[3][2].Close = 2506.35 ;
    Company[3][1].Close = 2488.6 ; 
    Company[3][0].Close = 2498.3 ;             

    Company[3][9].Volume = 776397;
    Company[3][8].Volume = 741025;
    Company[3][7].Volume = 874589;           
    Company[3][6].Volume = 776977;
    Company[3][5].Volume = 707543;
    Company[3][4].Volume = 803856;
    Company[3][3].Volume = 2278682;
    Company[3][2].Volume = 1804818;
    Company[3][1].Volume = 1627836; 
    Company[3][0].Volume = 1771910;

    // INTEL

    Company[4][9].Open = 8362 ;
    Company[4][8].Open = 8221 ;
    Company[4][7].Open = 8085 ;
    Company[4][6].Open = 8050 ;
    Company[4][5].Open = 8080  ;
    Company[4][4].Open = 8044.30  ;
    Company[4][3].Open = 7999.55    ;
    Company[4][2].Open = 8125 ;
    Company[4][1].Open = 8139.80 ;
    Company[4][0].Open = 8055  ;

    Company[4][9].High = 8184.64;
    Company[4][8].High = 8284.70;
    Company[4][7].High = 8224.40;
    Company[4][6].High = 8084.60;
    Company[4][5].High = 8159;
    Company[4][4].High = 8069;
    Company[4][3].High = 8082.90;
    Company[4][2].High = 8127;
    Company[4][1].High = 8173;
    Company[4][0].High = 8135;

    Company[4][9].Low = 7865;
    Company[4][8].Low = 7845;
    Company[4][7].Low = 7860;
    Company[4][6].Low = 7850;
    Company[4][5].Low = 8057.55;
    Company[4][4].Low = 7982.65;
    Company[4][3].Low = 7956.05;
    Company[4][2].Low = 8003 ;
    Company[4][1].Low = 8095.45; 
    Company[4][0].Low = 8021 ;

    Company[4][9].Close = 7884.45;
    Company[4][8].Close = 7874.25;
    Company[4][7].Close = 7889.35;
    Company[4][6].Close = 7866.55;
    Company[4][5].Close = 8093;
    Company[4][4].Close = 8036;
    Company[4][3].Close = 8051.65;
    Company[4][2].Close = 8014.30 ;
    Company[4][1].Close = 8101.95; 
    Company[4][0].Close = 8083.60 ;             
                        
    Company[4][9].Volume = 12521478;
    Company[4][8].Volume = 12025363;
    Company[4][7].Volume = 12025147;
    Company[4][6].Volume = 12000153;
    Company[4][5].Volume = 838283;
    Company[4][4].Volume = 438246;
    Company[4][3].Volume = 662282;
    Company[4][2].Volume = 764092;
    Company[4][1].Volume = 712372; 
    Company[4][0].Volume = 965024;

    // FACEBOOK

    Company[5][9].Open = 138 ;
    Company[5][8].Open = 145 ;
    Company[5][7].Open = 189.25 ;
    Company[5][6].Open = 188 ;
    Company[5][5].Open = 187 ;
    Company[5][4].Open = 187.95  ;
    Company[5][3].Open = 184.5  ;
    Company[5][2].Open = 183.2 ;
    Company[5][1].Open = 184.4    ;
    Company[5][0].Open = 182.3  ;

    Company[5][9].High = 175.05;
    Company[5][8].High = 186.05;
    Company[5][7].High = 184.45;
    Company[5][6].High = 188.25;
    Company[5][5].High = 187.05;
    Company[5][4].High = 188.2;
    Company[5][3].High = 186.25;
    Company[5][2].High = 184.85;
    Company[5][1].High = 184.7;
    Company[5][0].High = 184.5;

    Company[5][9].Low = 182.15;
    Company[5][8].Low = 184.17;
    Company[5][7].Low = 188.16;
    Company[5][6].Low = 186.25;
    Company[5][5].Low = 185.55;
    Company[5][4].Low = 186.25;
    Company[5][3].Low = 184.05;
    Company[5][2].Low = 183 ;
    Company[5][1].Low = 182.75; 
    Company[5][0].Low = 182.05 ;

    Company[5][9].Close = 186.21;
    Company[5][8].Close = 182.47;
    Company[5][7].Close = 184.84;
    Company[5][6].Close = 192.92;
    Company[5][5].Close = 186.25;
    Company[5][4].Close = 186.55;
    Company[5][3].Close = 184.9;
    Company[5][2].Close = 184.45 ;
    Company[5][1].Close = 183.25; 
    Company[5][0].Close = 183.5 ;             
                        
    Company[5][9].Volume = 21453698;
    Company[5][8].Volume = 10158142;
    Company[5][7].Volume = 10152146;              
    Company[5][6].Volume = 10181113;
    Company[5][5].Volume = 4381065;
    Company[5][4].Volume = 12376549;
    Company[5][3].Volume = 7435899;
    Company[5][2].Volume = 8677885;
    Company[5][1].Volume = 8499601; 
    Company[5][0].Volume = 11819690;

    // GOOGLE
  
    Company[6][9].Open = 406 ;
    Company[6][8].Open = 407 ;
    Company[6][7].Open = 408 ;
    Company[6][6].Open = 409 ;
    Company[6][5].Open = 411.7  ;
    Company[6][4].Open = 411  ;
    Company[6][3].Open = 411.9  ;
    Company[6][2].Open = 421.75 ;
    Company[6][1].Open = 409    ;
    Company[6][0].Open = 406.4  ;

    Company[6][9].High = 453.85;
    Company[6][8].High = 443.75;
    Company[6][7].High = 433.55;
    Company[6][6].High = 413.65;
    Company[6][5].High = 413.85;
    Company[6][4].High = 411.9;
    Company[6][3].High = 414.4;
    Company[6][2].High =  421.9;
    Company[6][1].High =  423.95;
    Company[6][0].High =  408.75;

    Company[6][9].Low = 408;
    Company[6][8].Low = 413;
    Company[6][7].Low = 415;
    Company[6][6].Low = 407;
    Company[6][5].Low = 411.05;
    Company[6][4].Low = 408.15;
    Company[6][3].Low = 409.05;
    Company[6][2].Low = 414.7 ;
    Company[6][1].Low = 409; 
    Company[6][0].Low = 406.2 ;

    Company[6][9].Close = 448.69;
    Company[6][8].Close = 477.75;
    Company[6][7].Close = 417.65;
    Company[6][6].Close = 407.45;
    Company[6][5].Close = 411.4;
    Company[6][4].Close = 410.2;
    Company[6][3].Close = 411.05;
    Company[6][2].Close = 417.1 ;
    Company[6][1].Close = 421.15; 
    Company[6][0].Close = 407.75 ;             

    Company[6][9].Volume = 2258741;                   
    Company[6][8].Volume = 2436153;
    Company[6][7].Volume = 2478453;
    Company[6][6].Volume = 2445213;
    Company[6][5].Volume = 2989694;
    Company[6][4].Volume = 2638826;
    Company[6][3].Volume = 5457027;
    Company[6][2].Volume = 1804818;
    Company[6][1].Volume = 9546114; 
    Company[6][0].Volume = 2564007;

    // TCS

    Company[7][9].Open = 2356.75 ;
    Company[7][8].Open = 2357.85 ;
    Company[7][7].Open = 2365.45 ;
    Company[7][6].Open = 2355.25 ;
    Company[7][5].Open = 2356  ;
    Company[7][4].Open = 2340 ;
    Company[7][3].Open = 2340    ;
    Company[7][2].Open = 2343.85 ;
    Company[7][1].Open = 2314.45   ;
    Company[7][0].Open = 2306.55 ;

    Company[7][9].High = 2385 ;
    Company[7][8].High = 2375 ;
    Company[7][7].High = 2370 ;
    Company[7][6].High = 2367 ;
    Company[7][5].High = 2359.70;
    Company[7][4].High = 2354.55;
    Company[7][3].High = 2357.50;
    Company[7][2].High = 2359.35;
    Company[7][1].High = 2349.70;
    Company[7][0].High = 2317.90;

    Company[7][9].Low = 2336;
    Company[7][8].Low = 2345;
    Company[7][7].Low = 2325;
    Company[7][6].Low = 2321;
    Company[7][5].Low = 2341.30;
    Company[7][4].Low = 2336;
    Company[7][3].Low = 2329.15;
    Company[7][2].Low = 2338.15 ;
    Company[7][1].Low = 2313; 
    Company[7][0].Low = 2303.75 ;

    Company[7][9].Close = 2348;
    Company[7][8].Close = 2396;
    Company[7][7].Close = 2332;
    Company[7][6].Close = 2324;
    Company[7][5].Close = 2355.25;
    Company[7][4].Close = 2344.05;
    Company[7][3].Close = 2349.30;
    Company[7][2].Close = 2349.40 ;
    Company[7][1].Close = 2345.05; 
    Company[7][0].Close = 2308.40 ;             
                        
    Company[7][9].Volume = 44568472;
    Company[7][8].Volume = 4455621;
    Company[7][7].Volume = 45412078;
    Company[7][6].Volume = 4459160;
    Company[7][5].Volume = 3964090;
    Company[7][4].Volume = 12376549;
    Company[7][3].Volume = 5075158;
    Company[7][2].Volume = 1804818;
    Company[7][1].Volume = 4907059; 
    Company[7][0].Volume = 5118016;

    // ALIBABA

    Company[8][9].Open = 458.65 ;
    Company[8][8].Open = 456.75 ;
    Company[8][7].Open = 455.45 ;
    Company[8][6].Open = 454.25 ;
    Company[8][5].Open = 449.8  ;
    Company[8][4].Open = 448  ;
    Company[8][3].Open = 449.85 ;
    Company[8][2].Open = 449.65 ;
    Company[8][1].Open = 447.2  ;
    Company[8][0].Open = 440.45 ;

    Company[8][9].High = 496.2;
    Company[8][8].High = 464.2;
    Company[8][7].High = 459.25;
    Company[8][6].High = 458.2;
    Company[8][5].High = 454.5;
    Company[8][4].High = 451;
    Company[8][3].High = 451.8;
    Company[8][2].High = 452.5;
    Company[8][1].High = 449.45;
    Company[8][0].High = 444.85;

    Company[8][9].Low = 451;
    Company[8][8].Low = 447;
    Company[8][7].Low = 445;
    Company[8][6].Low = 451;
    Company[8][5].Low = 449;
    Company[8][4].Low = 446.2;
    Company[8][3].Low = 447;
    Company[8][2].Low = 446.15;
    Company[8][1].Low = 444.8; 
    Company[8][0].Low = 440.45 ;

    Company[8][9].Close = 459.35;
    Company[8][8].Close = 467.55;
    Company[8][7].Close = 464.75;
    Company[8][6].Close = 451.65;
    Company[8][5].Close = 453.45;
    Company[8][4].Close = 448.95;
    Company[8][3].Close = 448.35;
    Company[8][2].Close = 450.7 ;
    Company[8][1].Close = 448.25; 
    Company[8][0].Close = 444.4 ;             
                        
    Company[8][9].Volume = 6887417;
    Company[8][8].Volume = 6896327;
    Company[8][7].Volume = 6885477;                   
    Company[8][6].Volume = 6894947;
    Company[8][5].Volume = 6936218;
    Company[8][4].Volume = 4214958;
    Company[8][3].Volume = 7632483;
    Company[8][2].Volume = 11774487;
    Company[8][1].Volume = 7651513; 
    Company[8][0].Volume = 5014758;

    // HCL

    Company[9][9].Open = 485 ;
    Company[9][8].Open = 385 ;
    Company[9][7].Open = 395 ;
    Company[9][6].Open = 355 ;
    Company[9][5].Open = 348.90 ;
    Company[9][4].Open = 345 ;
    Company[9][3].Open = 347.10    ;
    Company[9][2].Open = 344.90 ;
    Company[9][1].Open = 342.20    ;
    Company[9][0].Open = 340.05  ;

    Company[9][9].High = 486.57;
    Company[9][8].High = 402.56;
    Company[9][7].High = 425.43;
    Company[9][6].High = 400.50;
    Company[9][5].High = 396.70;
    Company[9][4].High = 382.45;
    Company[9][3].High = 369.60;
    Company[9][2].High =  789.35;
    Company[9][1].High =  578.30;
    Company[9][0].High =  552.60;

    Company[9][9].Low = 333.85;
    Company[9][8].Low = 333.85;
    Company[9][7].Low = 333.85;
    Company[9][6].Low = 333.85;
    Company[9][5].Low = 344.70;
    Company[9][4].Low = 342.85;
    Company[9][3].Low = 340.05;
    Company[9][2].Low = 324.05 ;
    Company[9][1].Low = 211.50; 
    Company[9][0].Low = 189.20 ;

    Company[9][9].Close = 385.52;
    Company[9][8].Close = 350.65;
    Company[9][7].Close = 355.58;
    Company[9][6].Close = 350.52;
    Company[9][5].Close = 354.74;
    Company[9][4].Close = 347.28;
    Company[9][3].Close = 347.49;
    Company[9][2].Close = 344.89;
    Company[9][1].Close = 342.02; 
    Company[9][0].Close = 340.70 ;             

    Company[9][9].Volume = 4147526;
    Company[9][8].Volume = 4881452;
    Company[9][7].Volume = 4651243;                    
    Company[9][6].Volume = 4581119;
    Company[9][5].Volume = 6936228;
    Company[9][4].Volume = 1631258;
    Company[9][3].Volume = 1990920;
    Company[9][2].Volume = 3851950;
    Company[9][1].Volume = 2399748; 
    Company[9][0].Volume = 1786447;

    int start,end ;
    printf("Enter start date: ");
    scanf("%d",&start);
    printf("Enter end date: ");
    scanf("%d",&end);

    percentagechangeinstock(Company,start,end) ;

    int buy_date,selling_date ;
    printf("Enter start date: ");
    scanf("%d",&buy_date);
    printf("Enter end date: ");
    scanf("%d",&selling_date);

   int day_to_sort;
    printf("Enter the day to sort stock data (0-9): ");
    scanf("%d", &day_to_sort);

    if (day_to_sort < 0 || day_to_sort >= num_of_days) {
        printf("Invalid day input. Please enter a day between 0 and %d\n", num_of_days - 1);
        return 1; // Exit the program with an error status
    }

    sortStockVolumeClose(Company, day_to_sort);

    // Print the sorted stock data
    printf("Sorted Stock Data based on Volume and Close Price for Day %d:\n", day_to_sort);
    for (int i = 0; i < num_of_com; i++) {
        printf("Stock Name: %s, Volume: %.2f, Close Price: %.2f\n", Company[i][day_to_sort].name, Company[i][day_to_sort].Volume, Company[i][day_to_sort].Close);
    }
    
    printf("Enter start date: ");
    scanf("%d",&buy_date);
    printf("Enter end date: ");
    scanf("%d",&selling_date);
    profitloss(Company,buy_date,selling_date); 
    printf("\n\n");
    

    printf("Enter start date: ");
    scanf("%d",&buy_date);
    printf("Enter end date: ");
    scanf("%d",&selling_date);
    printf("Highest Profit of stock:\n");
    highestprofit(Company,buy_date,selling_date);
     printf("\n\n");
     printf("Lowest Profit of stock :\n");
     lowestprofit(Company,buy_date,selling_date);
     printf("\n\n");

    printf("Enter start date: ");
    scanf("%d",&start);
    printf("Enter end date: ");
    scanf("%d",&end);
     printf("Overall performance of stocks from start date to end date is:\n");
      overallperformance(Company, start, end);
      printf("\n\n");

    printf("Enter start date: ");
    scanf("%d",&start);
    printf("Enter end date: ");
    scanf("%d",&end);
     printf("Average of average values of all stocks from start to end date:\n");
      averageofaverage(Company, start, end);

    return 0;
}
#include <string.h>
#include <time.h>
#include  <stdio.h>
#include <stdlib.h>
int temperature = 0;
FILE *file;
char line[256];
char name [100];
long value = 0;
char kb[20];
int dostepna = 0;
int calkowita = 0;
//pozmieniac troche errory ale poki co jest git
int read_temp(FILE *file)
{
	file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	if(file == NULL)
	{
	perror("bład odczytu");
	return 1;
	}
	if(fscanf(file, "%d", &temperature) == 1)
	{
	printf("\033[K%.2f", temperature / 1000.00);
	}
	else
	{
	perror("jest bład");
	return 1;
	}
	fclose(file);
	return 0;
}
int read_ram(FILE *file)
{
	file = fopen("/proc/meminfo", "r");
	while(file != NULL)
	{
	if(fgets(line, sizeof(line), file) != NULL)
	{
	sscanf(line, "%99s %ld %19s", name, &value, kb);
	if(strcmp(name, "MemTotal:") == 0)
	{
	calkowita = value;
	printf("\033[1E\033[K %s %ld %s" , name, value, kb);
	}
	if(strcmp(name, "MemFree:") == 0)
	{
	dostepna = value;
	printf("\033[1E\033[K%s %ld %s", name, value, kb);
	break;
	}
	}
	}
	fclose(file);
	return 0;
}
int read_cpu_time(FILE *file)
{
	file = fopen("/proc/uptime", "r");
	int uptime = 0;
	int seconds = 0;
	int suma_minut = 0;
	int minutes = 0;
	int hours = 0;
	if(file != NULL)
	{
	fscanf(file, "%d", &uptime);
	seconds = uptime % 60;
	suma_minut = uptime / 60;
	minutes = suma_minut % 60;
	hours = suma_minut / 60;
	printf("\033[1E\033[K%d, %d, %d, %d", hours, minutes, seconds, uptime);
	}
	fclose(file);
	return 0;
}
int read_cpu_load(FILE *file)
{
	double minutes, minutess, minutesss = 0;
	file = fopen("/proc/loadavg", "r");
	if(file != NULL)
	{
	fscanf(file,"%lf %lf %lf", &minutes, &minutess, &minutesss);
	printf("\033[1E\033[K%lf %lf %lf", minutes, minutess, minutesss);
	}
	fclose(file);
	return 0;
}
int data_sent(FILE *file)
{
	long rx_bytes = 0;
	long rx_packets = 0;
	long tx_bytes = 0;
	long tx_packets = 0;
	long data[16];
	file = fopen("/proc/net/dev", "r");
	while(file != NULL)
	{
	fgets(line, sizeof(line), file);
	if(strstr(line, "wlan0") != 0)
	{
	char *ptr = strchr(line, ':');
	if(ptr != NULL)
	{
	ptr++;
	for(int i = 0; i < 16; i++)
	{
	 data[i] = strtol(ptr, &ptr, 10);
	}
	 rx_bytes = data[0];
	 rx_packets =  data[1];
	 tx_bytes = data[8];
	 tx_packets = data[9];
	}
	printf("\033[1E\033[K%ld %ld %ld %ld", rx_bytes, rx_packets, tx_bytes, tx_packets);
	break;
	}
	}
	fclose(file);
	return 0;

}
int main(void)
{
struct timespec time;
time_t last = 0;
while(1)
{
	clock_gettime(CLOCK_MONOTONIC, &time);
	//printf("\r%lld, %lld", (long long)time.tv_sec, (long long)last);
	fflush(stdout);
	if(time.tv_sec - last > 10)
	{
	read_temp(file);
	read_ram(file);
	read_cpu_time(file);
	read_cpu_load(file);
	data_sent(file);
	printf("\r\033[4A");
	}
        struct timespec pause = {0, 10000000L};
        nanosleep(&pause, NULL);
}
return 0;
}

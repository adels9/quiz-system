#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct podaci
{
    char ime[30];
    char prezime[30];
    char user[30];
    char pass[20];
    char admin[10];
};

struct pitanja
{
    int id;
    char pitanje[5][50];
    char odgovor1[3][20];
    char odgovor2[3][20];
    char odgovor3[3][20];
    char odgovor4[3][20];
    char odgovor5[3][20];
    int tacni_odg[5];
};

void prijava(void);
void registracija (void);

int main(void)
{
    int izbor;
    printf("Izaberite:\n\n1. Registracija\n2. Prijava\n");
    printf("\nVas izbor: ");
    scanf("%d",&izbor);
    getchar();

    if(izbor == 1)
    {
            system("CLS");
            registracija();
    }

    else if(izbor == 2)
    {
            system("CLS");
            prijava();
    }
}

void prijava (void)
{
    POCETAK:
    system("cls");
    char pime[30], pprezime[30], user[30], pass[20], user2[30], pass2[20], adm[10], padmin[10], pregled_ime[30], pregled_prezime[30], k_ime[30], pozicija[10], unos_pitanja[30], unos_pitanjaa[30];
    int prijava = 0, izbor, tacan_odg;
    FILE *log, *temp, *kv1, *kv2, *kv3;

    log = fopen("Korisnici.txt","r");
    if (log == NULL)
    {
        fputs("Greska", stderr);
        exit(1);
    }

    struct podaci l;

    printf("\nMolimo unesite podatke za prijavu ispod\n\n");
    printf("Korisnicko ime: ");
    scanf("%s", user);
    printf("\nLozinka: ");
    scanf("%s", pass);

    while(fscanf(log, "%s %s %s %s %s", &pime[0], &pprezime[0], &user2[0], &pass2[0], &adm[0]) != EOF)
    {
        if(strcmp(user,user2)==0 && strcmp(pass,pass2)==0)
        {
            prijava = 1;
            strcpy(padmin, adm);
            strcpy(pregled_ime, pime);
            strcpy(pregled_prezime, pprezime);
        }
    }

    fclose(log);
    if(prijava == 1)
    {
        printf("\nUspjesna prijava.\n");
        sleep(2);
        GL_MENI:
        if(strcmp(padmin, "Student") == 0)
        {
            system("cls");
            printf("\nPozdrav, %s. Izaberite neku opciju.\n", user);
            printf("\n1. Pregled licnog profila\n2. Pristupanje ispitnim aktivnostima\n3. Zatvori program\n\nVas izbor: ");
            scanf("%d", &izbor);
            switch(izbor)
            {
                case 1:
                    goto PREGLED_PROFILA;
                    break;
                case 2:
                    goto PRISTUPI_AKTIVNOSTIMA;
                    break;
                case 3:
                    return;
                    break;
            }
        }
        else
        {
            system("cls");
            printf("\nPozdrav, %s. Izaberite neku opciju.\n", user);
            printf("\n1. Kreiraj novog korisnika\n2. Uredi korisnika\n3. Brisanje korisnika\n4. Pregled svih korisnika\n5. Kreiranje ispitnih aktivnosti\n6. Zatvori program\n\nVas izbor: ");
            scanf("%d", &izbor);
            switch(izbor)
            {
                case 1:
                    goto KREIRAJ_KORISNIKA;
                    break;
                case 2:
                    goto UREDI_KORISNIKA;
                    break;
                case 3:
                    goto BRISANJE_KORISNIKA;
                    break;
                case 4:
                    goto SVI_KORISNICI;
                    break;
                case 5:
                    goto ISPITNE_AKTIVNOSTI;
                    break;
                case 6:
                    return;
            }
        }
    }
    else
    {
        printf("\nPogresni podaci.\nMolimo unesite tacne podatke.\n");
        sleep(3);
        goto POCETAK;
    }
    PREGLED_PROFILA:
    system("cls");
    printf("Pregled licnog profila\n\nKorisnicko ime: %s\n", user);
    printf("Ime: %s\n", pregled_ime);
    printf("Prezime: %s\n", pregled_prezime);
    printf("Pozicija: %s\n", padmin);
    printf("\n\nDa se vratite nazad pritisnite enter\n");
    char ch;
    scanf("%c%*c", &ch);
    if(ch == 10) goto GL_MENI;
    KREIRAJ_KORISNIKA:
    log = fopen("Korisnici.txt","a");
    if (log == NULL)
    {
        fputs("Greska", stderr);
        exit(1);
    }
    system("cls");
    struct podaci nk;
    printf("Kreiranje korisnika\n\nUnesite ime: ");
    scanf("%s",&nk.ime);
    printf("\nUnesite prezime:\n");
    scanf("%s",&nk.prezime);
    printf("\nUnesite korisnicko ime:\n");
    scanf("%s",&nk.user);
    printf("\nUnesite lozinku:\n");
    scanf("%s",&nk.pass);
    fflush(stdin);
    printf("\nUnesite poziciju (Student ili Profesor): ");
    scanf("%s",&nk.admin);
    fprintf(log, "%s %s %s %s %s\n", &nk.ime, &nk.prezime, &nk.user, &nk.pass, &nk.admin);
    fclose(log);
    system("cls");
    printf("Uspjesno ste dodali korisnika.\n\nIme: %s\nPrezime: %s\nKorisnicko ime: %s\nLozinka: %s\nPozicija: %s", nk.ime, nk.prezime, nk.user, nk.pass, nk.admin);
    printf("\n\nDa se vratite nazad pritisnite enter\n");
    scanf("%c%*c", &ch);
    if(ch == 10) goto GL_MENI;
    UREDI_KORISNIKA:
    system("cls");
    printf("Unesite korisnicko ime korisnika kojeg zelite urediti: ");
    fflush(stdin);
    scanf("%s", &k_ime);
    log=fopen("Korisnici.txt","r");
    temp=fopen("temp.txt", "w");
    while(fscanf(log, "%s %s %s %s %s", &pime[0], &pprezime[0], &user2[0], &pass2[0], &adm[0]) != EOF)
    {
        if(strcmp(k_ime, user2) == 0)
        {
            char unos[30];
            system("cls");
            printf("Uredjujete podatke korisnika %s.\n\nOdaberite sta zelite urediti:\n\n1. Ime\n2. Prezime\n3. Korisnicko ime\n4. Lozinku\n5. Poziciju\n\nVas izbor: ", k_ime);
            scanf("%d", &izbor);
            switch(izbor)
            {
                case 1:
                    system("cls");
                    printf("Uredjujete ime korisnika, unesite novo ime: ");
                    scanf("%s", &unos);
                    fprintf(temp, "%s %s %s %s %s\n", &unos, &pprezime, &user2, &pass2, &adm);
                    printf("\n\nUspjesno ste azurirali ime korisnika na %s.", unos);
                    break;
                case 2:
                    system("cls");
                    printf("Uredjujete prezime korisnika, unesite novo prezime: ");
                    scanf("%s", &unos);
                    fprintf(temp, "%s %s %s %s %s\n", &pime, &unos, &user2, &pass2, &adm);
                    printf("\n\nUspjesno ste azurirali prezime korisnika na %s.", unos);
                    break;
                case 3:
                    system("cls");
                    printf("Uredjujete korisnicko ime, unesite novo: ");
                    scanf("%s", &unos);
                    fprintf(temp, "%s %s %s %s %s\n", &pime, &pprezime, &unos, &pass2, &adm);
                    printf("\n\nUspjesno ste azurirali korisnicko ime na %s.", unos);
                    break;
                case 4:
                    system("cls");
                    printf("Uredjujete lozinku, unesite novu lozinku korisnika: ");
                    scanf("%s", &unos);
                    fprintf(temp, "%s %s %s %s %s\n", &pime, &pprezime, &user2, &unos, &adm);
                    printf("\n\nUspjesno ste azurirali lozinku na %s.", unos);
                    break;
                case 5:
                    system("cls");
                    printf("Uredjujete poziciju korisnika, unesite novu (Student ili Profesor): ");
                    scanf("%s", &unos);
                    fprintf(temp, "%s %s %s %s %s\n", &pime, &pprezime, &user2, &pass2, &unos);
                    printf("\n\nUspjesno ste azurirali poziciju korisnika.");
                    break;
            }
        }
        else
        {
            fprintf(temp, "%s %s %s %s %s\n", &pime, &pprezime, &user2, &pass2, &adm);
        }
    }
    fclose(log);
    fclose(temp);
    remove("Korisnici.txt");
    rename("temp.txt", "Korisnici.txt");
    printf("\n\nDa se vratite nazad pritisnite enter\n");
    scanf("%c%*c", &ch);
    if(ch == 10) goto GL_MENI;
    //BRISANJE
    BRISANJE_KORISNIKA:
    system("cls");
    printf("Unesite korisnicko ime korisnika kojeg zelite obrisati: ");
    fflush(stdin);
    scanf("%s", &k_ime);
    log=fopen("Korisnici.txt","r");
    temp=fopen("temp.txt", "w");
    while(fscanf(log, "%s %s %s %s %s", &pime[0], &pprezime[0], &user2[0], &pass2[0], &adm[0]) != EOF)
    if(strcmp(k_ime, user2) != 0) fprintf(temp, "%s %s %s %s %s\n", &pime, &pprezime, &user2, &pass2, &adm);
    fclose(log);
    fclose(temp);
    remove("Korisnici.txt");
    rename("temp.txt", "Korisnici.txt");
    printf("\n\nUspjesno ste obrisali korisnika %s.", k_ime);
    sleep(2);
    goto GL_MENI;
    //PREGLED SVIH KORISNIKA
    SVI_KORISNICI:
    system("cls");
    printf("Pregled svih korisnika\n\n");
    log=fopen("Korisnici.txt","r");
    while(fscanf(log, "%s %s %s %s %s", &pime[0], &pprezime[0], &user2[0], &pass2[0], &adm[0]) != EOF)
    printf("Ime: %s \t\tPrezime: %s \t\tKorisnicko ime: %s \t\tPozicija: %s\n", pime, pprezime, user2, adm);
    fclose(log);
    printf("\n\nDa se vratite nazad pritisnite enter\n");
    scanf("%c%*c", &ch);
    if(ch == 10) goto GL_MENI;
    //DODAVANJE ISPITNIH AKTIVNOSTI
    ISPITNE_AKTIVNOSTI:
    system("cls");
    kv1=fopen("Pitanja.txt","w");
    kv2=fopen("Odgovori.txt","w");
    kv3=fopen("Tacni.txt","w");
    printf("Morate unijeti 5 pitanja.");
    for(int i = 1; i < 6; i++)
    {
        char str[100];
        system("cls");
        printf("\n\nUnesite pitanje broj %d: ", i);
        getchar();
        fgets(str, 100, stdin);
        fprintf(kv1, "%s", &str);
        for(int j = 1; j < 4; j++)
        {
            printf("Unesite odgovor broj %d: ", j);
            scanf("%s", &unos_pitanja);
            fprintf(kv2, "%s\n", &unos_pitanja);
        }
        printf("Unesite koji je odgovor tacan za postavljeno pitanje (1, 2 ili 3): ");
        scanf("%d", &tacan_odg);
        fprintf(kv3, "%d\n", tacan_odg);
    }
    fclose(kv1);
    fclose(kv2);
    fclose(kv3);
    system("cls");
    printf("Ispitne aktivnosti uspjesno dodane, prebacujemo vas na glavni meni.");
    sleep(3);
    goto GL_MENI;
    //PRISTUPANJE STUDENTA AKTIVNOSTIMA
    PRISTUPI_AKTIVNOSTIMA:
    kv1=fopen("Pitanja.txt","r");
    kv2=fopen("Odgovori.txt", "r");
    kv3=fopen("Tacni.txt", "r");
    int brojac = 0;
    struct pitanja nova;
    char str[50];
    int str2, k_odg[5];
    while(fgets(str,50, kv1))
    {
        strcpy(nova.pitanje[brojac], str);
        brojac++;
    }
    brojac = 0;
    while(fgets(str,50, kv2))
    {
        if(brojac <= 2)
        {
           strcpy(nova.odgovor1[brojac], str);
        }
        if(brojac <= 5)
        {
           strcpy(nova.odgovor2[brojac], str);
        }
        if(brojac <= 8)
        {
           strcpy(nova.odgovor3[brojac], str);
        }
        if(brojac <= 11)
        {
           strcpy(nova.odgovor4[brojac], str);
        }
        if(brojac <= 14)
        {
           strcpy(nova.odgovor5[brojac], str);
        }
        brojac++;
    }
    brojac = 0;
    while(fscanf(kv3, "%d", &str2) != EOF)
    {
        nova.tacni_odg[brojac] = str2;
        brojac++;
    }
    system("cls");
    printf("%s\n\n1. %s\n2. %s\n3. %s\n\nVas odgovor: ", nova.pitanje[0], nova.odgovor1[0], nova.odgovor1[1], nova.odgovor1[2]);
    scanf("%d", &k_odg[0]);
    system("cls");
    printf("%s\n\n1. %s\n2. %s\n3. %s\n\nVas odgovor: ", nova.pitanje[1], nova.odgovor2[0], nova.odgovor2[1], nova.odgovor2[2]);
    scanf("%d", &k_odg[1]);
    system("cls");
    printf("%s\n\n1. %s\n2. %s\n3. %s\n\nVas odgovor: ", nova.pitanje[2], nova.odgovor3[0], nova.odgovor3[1], nova.odgovor3[2]);
    scanf("%d", &k_odg[2]);
    system("cls");
    printf("%s\n\n1. %s\n2. %s\n3. %s\n\nVas odgovor: ", nova.pitanje[3], nova.odgovor4[0], nova.odgovor4[1], nova.odgovor4[2]);
    scanf("%d", &k_odg[3]);
    system("cls");
    printf("%s\n\n1. %s\n2. %s\n3. %s\n\nVas odgovor: ", nova.pitanje[4], nova.odgovor5[0], nova.odgovor5[1], nova.odgovor5[2]);
    scanf("%d", &k_odg[4]);
    brojac = 0;
    system("cls");
    for(int i=0; i<5; i++)
    {
        if(k_odg[i] == nova.tacni_odg[i])
        {
            brojac++;
        }
    }
    printf("Zavrsili ste ispitne aktivnosti.\n\nTacnih odgovora: %d/5", brojac);
    printf("\n\nDa se vratite nazad pritisnite enter\n");
    scanf("%c%*c", &ch);
    if(ch == 10) goto GL_MENI;
    return;
}




void registracija(void)
{
    FILE *log;
    log=fopen("Korisnici.txt","a");
    if (log == NULL)
    {
        printf("Greska", stderr);
        exit(1);
    }

    struct podaci novi;
    printf("\nIzabrali ste registraciju.\n\n");
    printf("\nUnesite ime (bez prezimena):\n");
    scanf("%s",&novi.ime);
    printf("\nUnesite prezime:\n");
    scanf("%s",&novi.prezime);
    printf("\nUnesite korisnicko ime:\n");
    scanf("%s",&novi.user);
    printf("\nUnesite lozinku:\n");
    scanf("%s",&novi.pass);
    fprintf(log, "%s %s %s %s %s\n", &novi.ime, &novi.prezime, &novi.user, &novi.pass, "Student");
    fclose(log);
    system("cls");
    printf("\nPozdrav, %s!\n", novi.ime);
    printf("\nRegistracija uspjesna, prebacujemo vas na login formu!\n");
    sleep(4);
    prijava();
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MusicPlayer { // Struct lagu
    char judul[101];
    struct MusicPlayer* next;
    struct MusicPlayer* prev;
}*head, *tail, *current;

int song_count = 0; // buat ID

void addSong(const char* title) { // Function push
    MusicPlayer* newSong = (struct MusicPlayer*)malloc(sizeof(MusicPlayer)); // alokasiin memory buat node baru pake malloc
    strcpy(newSong->judul, title);
    song_count++;
    if (head == NULL) {
        head = tail = newSong;
        head->next = head;
        head->prev = head;
    } else {
        newSong->prev = tail;
        newSong->next = head;
        tail->next = newSong;
        head->prev = newSong;
        tail = newSong;
    }
}

void showPlaylist() {
    if (head == NULL) {
        printf("Playlist kosong!\n");
        return;
    }

    printf("Playlist:\n");
    struct MusicPlayer* current = head;
    int index = 1;
    do {
        printf("%d. %s\n", index++, current->judul);
        current = current->next;
    } while (current != head);
}

void playNext() {
    if (current == NULL) {
        current = head;
    } else {
        current = current->next;
    }
    printf("Now playing: %s\n", current->judul);
}

void playPrevious() {
    if (current == NULL) {
        current = head;
    } else {
        current = current->prev;
    }
    printf("Now playing: %s\n", current->judul);
}

void playOnce() {
    if (current == NULL) {
        current = head;
    }
    printf("Now playing: %s\n", current->judul);
    current = NULL; // Stop after one play
}

void playLoop(int times) {
    if (head == NULL) {
        printf("Playlist kosong!\n");
        return;
    }

    if (current == NULL) {
        current = head;
    }
    
    for (int i = 0; i < times; i++) {
        printf("Now playing: %s\n", current->judul);
    }
}

void selectSong(int songNumber) {
    if (head == NULL) {
        printf("Playlist kosong!\n");
        return;
    }

    if (songNumber < 1 || songNumber > song_count) {
        printf("Masukkin nomor yang bener woyy!!\n");
        return;
    }

    current = head; // Mulai dari head
    for (int i = 1; i < songNumber; i++) {
        current = current->next;
    }

    printf("Now playing: %s\n", current->judul);
}

int main() {
    int n;
    int song;
    printf("Berapa banyak lagu yang ingin kamu masukkan: ");
    scanf("%d", &n); getchar();

    for(int i = 0; i < n; i++){
        char *judul = (char*)malloc(sizeof(char));
        printf("Masukkan judul lagu %d: ", i+1);
        scanf("%[^\n]", judul); getchar();
        addSong(judul);
    }

    showPlaylist();
    printf("Lagu mana yang mau kamu dengerin?: ");
    scanf("%d", &song); getchar();
    selectSong(song);
    
    printf("Next Song >> \n");
    playNext();
    printf("\n");

    printf("Next Song >> \n");
    playNext();
    printf("\n");
    
    printf("Prev Song >> \n");
    playPrevious();
    printf("\n");

    printf("Lagu mana yang mau kamu dengerin sekali?: ");
    scanf("%d", &song); getchar();
    selectSong(song);
    playOnce();

    printf("Lagu mana yang mau kamu dengerin?: ");
    scanf("%d", &song); getchar();
    selectSong(song);
    int loop;
    printf("Berapa kali kamu akan loop lagu ini: ");
    scanf("%d", &loop);
    playLoop(loop);

    return 0;
}
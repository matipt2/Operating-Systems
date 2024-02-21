#define nazwaKolejki "/kolejka"
mqd_t tworzenie (const char *name, int oflag);
mqd_t otwieranie (const char *name, int oflag);
void wysylanie (mqd_t mq_des, const char *msg_ptr, unsigned int msg_prio);
void pobieranieAtrb(mqd_t mq_des);
void odbieranie (mqd_t mq_des, char *msg_ptr, unsigned int *msg_prio);
void zamykanie (mqd_t mq_des);
void usuwanie(const char *name);


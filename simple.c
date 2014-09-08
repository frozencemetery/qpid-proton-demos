#include <stdio.h>
#include <string.h>

#include <proton/message.h>
#include <proton/messenger.h>
#include <proton/sasl.h>
#include <proton/util.h>

#define MAGIC 1024

pn_messenger_t *messenger = NULL;

static void sendmsg(char *address, char *msgtext) {
  pn_message_t *message = pn_message();
  pn_message_set_address(message, address);

  pn_data_t *body = pn_message_body(message);
  pn_data_put_string(body, pn_bytes(strlen(msgtext), msgtext));

  pn_messenger_put(messenger, message);
  pn_messenger_send(messenger, -1);

  return;
}

static void recvmsg(void) {
  pn_message_t *message = pn_message();
  pn_messenger_recv(messenger, MAGIC);

  pn_messenger_get(messenger, message);

  char buf[MAGIC];
  size_t bufsize = MAGIC;
  pn_data_t *body = pn_message_body(message);
  pn_data_format(body, buf, &bufsize);
  buf[MAGIC - 1] = '\0';
  printf("Got: %s\n", buf);
  return;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <addr> <message>\n", argv[0]);
    return 1;
  }
  char *address = argv[1];
  char *message = argv[2];

  messenger = pn_messenger(NULL);
  pn_messenger_start(messenger); /* no-op */

  /* needs to happen *before* the send */
  pn_messenger_subscribe(messenger, address);

  sendmsg(address, message);
  recvmsg();

  return 0;
}

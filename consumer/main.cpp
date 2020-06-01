
#include <screen/screen.h>
#include <iostream>

int main() {
  std::cout << "consumer\n";

  screen_context_t screen_ctx;
  screen_create_context(&screen_ctx, SCREEN_APPLICATION_CONTEXT);

  screen_stream_t stream_c;
  screen_create_stream(&stream_c, screen_ctx);

  // get producers' stream
  screen_event_t event;
  int stream_p_id = -1;
  screen_stream_t stream_p = NULL;
  screen_buffer_t
      acquired_buffer; /* Buffer that's been acquired from a stream */

  /* Create an event so that you can retrieve an event from Screen. */
  screen_create_event(&event);
  while (1) {
    std::cout << "consumer) waiting evetns\n";
    int event_type = SCREEN_EVENT_NONE;
    int object_type;

    /* Get event from Screen for the consumer's context. */
    screen_get_event(screen_ctx, event, -1);

    /* Get the type of event from the event retrieved. */
    screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &event_type);

    /* Process the event if it's a SCREEN_EVENT_CREATE event. */
    if (event_type == SCREEN_EVENT_CREATE) {
      std::cout << "consumer) SCREEN_EVENT_CREATE\n";
      /* Determine that this event is due to a producer stream granting
       * permissions. */
      screen_get_event_property_iv(event, SCREEN_PROPERTY_OBJECT_TYPE,
                                   &object_type);

      if (object_type == SCREEN_OBJECT_TYPE_STREAM) {
        /* Get the handle for the producer's stream from the event. */
        screen_get_event_property_pv(event, SCREEN_PROPERTY_STREAM,
                                     (void **)&stream_p);

        if (stream_p != NULL) {
          /* Get the handle for the producer's stream ID from the event.
           * If there are multiple producers in the system, consumers can use
           * the producer's stream ID
           * as a way to verify whether the SCREEN_EVENT_CREATE event is from
           * the producer that the consumer
           * is expecting. In this example, we assume there's only one producer
           * in the system.
           */
          screen_get_stream_property_iv(stream_p, SCREEN_PROPERTY_ID,
                                        &stream_p_id);
        }
      }
    }
    if (event_type == SCREEN_EVENT_CLOSE) {
      std::cout << "consumer) SCREEN_EVENT_CLOSE\n";
      /* Determine that this event is due to a producer stream denying
       * permissions. */
      screen_get_event_property_iv(event, SCREEN_PROPERTY_OBJECT_TYPE,
                                   &object_type);

      if (object_type == SCREEN_OBJECT_TYPE_STREAM) {
        /* Get the handle for the producer's stream from the event. */
        screen_get_event_property_pv(event, SCREEN_PROPERTY_STREAM,
                                     (void **)&stream_p);

        if (stream_p != NULL) {
          /* Get the handle for the producer's stream ID from the event.
           * If there are multiple producers in the system, consumers can use
           * the producer's stream ID
           * as a way to verify whether the SCREEN_EVENT_CREATE event is from
           * the producer that the consumer
           * is expecting. In this example, we assume there's only one producer
           * in the system.
           */
          screen_get_stream_property_iv(stream_p, SCREEN_PROPERTY_ID,
                                        &stream_p_id);
          /* Release any buffers that have been acquired. */
          screen_release_buffer(acquired_buffer);
          /* Deregister asynchronous notifications of updates, if necessary.
             */
          screen_notify(screen_ctx, SCREEN_NOTIFY_UPDATE, stream_p, NULL);
          /* Destroy the consumer stream that's connected to this producer
             stream. */
          screen_destroy_stream(stream_c);
          /* Free up any resources that were locally allocated to track this
             stream. */
          screen_destroy_stream(stream_p);
        }
      }
    }
  }
  screen_destroy_event(event);
}


No inner algorithm detected

def round STARTVIEWCHANGE:
  SEND():

  send(all, message(PHASE, STARTVIEWCHANGE, NULL, NULL, p));

  UPDATE():

  old_0_p = p;
  if ((p == primary(view, n)))
  {
    old_0_vround = vround;
    if (((vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
    {
      vround = DOVIEWCHANGE;
    }
  }
  old_0_p = p;
  if (!(p == primary(view, n)))
  {
    old_2_vround = vround;
    if (((vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
    {
      vround = DOVIEWCHANGE;
    }
  }


def round DOVIEWCHANGE:
  SEND():

  if (!(old_0_p == primary(view, n)) && ((old_2_vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    send(primary(PHASE, n), message(PHASE, DOVIEWCHANGE, NULL, NULL, p, local_log()));
  }

  UPDATE():

  if ((old_0_p == primary(view, n)) && ((old_0_vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    old_1_vround = vround;
    if (((vround == DOVIEWCHANGE) && (count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f)))
    {
      computes_new_log();
      vround = STARTVIEW;
    }
  }
  if (!(old_0_p == primary(view, n)) && ((old_2_vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    vround = STARTVIEW;
  }


def round STARTVIEW:
  SEND():

  if ((old_0_p == primary(view, n)) && ((old_0_vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)) && ((old_1_vround == DOVIEWCHANGE) && (count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f)))
  {
    send(all, message(PHASE, STARTVIEW, NULL, NULL, p, local_log()));
  }

  UPDATE():

  if ((old_0_p == primary(view, n)) && ((old_0_vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)) && ((old_1_vround == DOVIEWCHANGE) && (count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f)))
  {
    vround = STARTVIEWCHANGE;
  }
  if (!(old_0_p == primary(view, n)) && ((old_2_vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    if (((vround == STARTVIEW) && (count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1)))
    {
      computes_new_log();
      vround = STARTVIEWCHANGE;
    }
  }


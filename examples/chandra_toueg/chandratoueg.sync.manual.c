INIT
    current_phase_round = jump_to();

FIRST_ROUND
    SEND:
        if(current_phase_round == (PHASE, ROUND)){
            if(!value_decided(p)){
                send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase,n)); 
            }
        }
    UPDATE:
        current_phase_round = jump_to();
        if(current_phase_round == (PHASE, ROUND)){
            condition1 = !value_decided(p) && p == leader(phase,n) && count(mbox, phase, FIRST_ROUND, null_int()) > (n+1)/2;

            if(condition1){
                round = SECOND_ROUND;
                m = max_timestamp(mbox);
                estimate = m->estimate;
            }
        }

SECOND_ROUND
    SEND:
      if(jump_to == (PHASE, ROUND)){
            if(!value_decided(p) && p == leader(phase,n) && condition1){
                send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
            }
        }

    UPDATE:
        jump_to = jump_to();
        if(jump_to == (PHASE, ROUND)){
            condition2 = !value_decided(p) && p != leader(phase,n) && count(mbox, phase, SECOND_ROUND, leader(phase,n)) == 1;

            // adding condition1 would contradict p != leader(phase,n)
            if(condition2){
                m = mbox->message;
                estimate = m->estimate;
                timestamp = phase;
            }
        }

THIRD_ROUND
    SEND:
        if(jump_to == (PHASE, ROUND)){
            if(!value_decided(p) && p != leader(phase,n) && condition2){
                send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase,n)); 
            }
        }

    UPDATE:
        jump_to = jump_to();
        if(jump_to == (PHASE, ROUND)){
            condition3 = !value_decided(p) && p == leader(phase,n) && count(mbox, phase, THIRD_ROUND, null_int()) > (n+1)/2 && all_ack(mbox);
            
            // adding condition2 would contradict p == leader(phase,n)
            // I see no reason to remove condition1
            if(condition3 && condition1){
                decide(estimate);
            }
        }

FOURTH_ROUND
    SEND:
        if(jump_to == (PHASE, ROUND)){
            if(p == leader(phase,n) && condition3){
                send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            }
            if(value_decided(p) && p == leader(phase,n)){
                send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            }
        }
    UPDATE:
        jump_to = jump_to();
        
        condition4 = p != leader(phase,n) && count(mbox, phase, FOURTH_ROUND, leader(phase,n)) == 1 && mbox->message->decided;
        
        // I see no reason to remove condition2
        if(jump_to == (PHASE, ROUND) || (condition4 && condition2)){
            estimate = m->estimate;
            decide(estimate);
        }
        // next phase
        jump_to = jump_to();

function matched = state_machine(din)
persistent state, state = xl_state(0,{xlUnsigned, 3, 0});
switch state
    %State - Current state of the state machine. In diagram, the number accompanying "S" in the bubbles. State has integral values belonging to [0,4] 
    %din - Choice/selection variable that dictates movement between states.
    %Values are shown in diagram.
    %Matched - Variable is set to HIGH/1 when state reaches 4. Otherwise,
    %reset.
    
    case 0 %State 0
        if din == 1
            state = 1; %Continue to State #1
        else
            state = 0; %Stay at State #0
        end 
        matched = 0; 
        
    case 1
        if din == 1
            state = 1; %Stay at State #0
        elseif din == 0
            state = 2; %Continue to State #2
        end
        matched = 0; 
        
    case 2
        if din == 1
            state = 3; %Stay at State #0
        elseif din == 0
            state = 0; %Continue to State #2
        end
        matched = 0;  
        
    case 3
        if din == 1
            state = 4; %Stay at State #0
        elseif din == 0
            state = 2; %Continue to State #2
        end
        matched = 0;  
    
    case 4
        if din == 1
            state = 1; %Stay at State #0
        elseif din == 0
            state = 0; %Continue to State #2
        end
        matched = 1;
        
    otherwise
        state=0;
        matched=0;
end
    
function n = din(As)
    global col1_in
    global col2_in
    global col3_in
    global col4_in
    
    ival = 20;

    size_As = size(As);
    n = size_As(2) / 8;
    n_timesteps = (size_As(2) + 7) * ival;
    
    col1_in.time = 0:n_timesteps - 1;
    col2_in.time = 0:n_timesteps - 1;
    col3_in.time = 0:n_timesteps - 1;
    col4_in.time = 0:n_timesteps - 1;
    col1_in.signals.dimensions = 1;
    col2_in.signals.dimensions = 1;
    col3_in.signals.dimensions = 1;
    col4_in.signals.dimensions = 1;
    
    col1_in.signals.values = zeros(n_timesteps, 1);
    col2_in.signals.values = zeros(n_timesteps, 1);
    col3_in.signals.values = zeros(n_timesteps, 1);
    col4_in.signals.values = zeros(n_timesteps, 1);
    
    col1_in.signals.values(1:size_As(2)) = As(1, 1:end);
    col2_in.signals.values(1:size_As(2)) = As(2, 1:end);
    col3_in.signals.values(1:size_As(2)) = As(3, 1:end);
    col4_in.signals.values(1:size_As(2)) = As(4, 1:end);
    
    for t = 0:size_As(2) - 1
        col1_in.signals.values(ival*t + 1 : ival*t + ival) = As(1, t + 1);
        col2_in.signals.values(ival*t + 1 : ival*t + ival) = As(2, t + 1);
        col3_in.signals.values(ival*t + 1 : ival*t + ival) = As(3, t + 1);
        col4_in.signals.values(ival*t + 1 : ival*t + ival) = As(4, t + 1); 
    end
end
function n = din_matmat(As, Bs)
    global wrap_in
    global row1_in
    global row2_in
    global row3_in
    global row4_in
    global col1_in
    global col2_in
    global col3_in
    global col4_in

    size_As = size(As);
    n = size_As(2) / 4;
    n_timesteps = size_As(2) + 6;
    
    wrap_in.time = 0:n_timesteps - 1;
    wrap_in.signals.dimensions = 1;
    wrap_in.signals.values = zeros(n_timesteps, 1);
    wrap_in.signals.values(1,1:end) = 3;
    
    row1_in.time = 0:n_timesteps - 1;
    row2_in.time = 0:n_timesteps - 1;
    row3_in.time = 0:n_timesteps - 1;
    row4_in.time = 0:n_timesteps - 1;
    row1_in.signals.dimensions = 1;
    row2_in.signals.dimensions = 1;
    row3_in.signals.dimensions = 1;
    row4_in.signals.dimensions = 1;
    col1_in.time = 0:n_timesteps - 1;
    col2_in.time = 0:n_timesteps - 1;
    col3_in.time = 0:n_timesteps - 1;
    col4_in.time = 0:n_timesteps - 1;
    col1_in.signals.dimensions = 1;
    col2_in.signals.dimensions = 1;
    col3_in.signals.dimensions = 1;
    col4_in.signals.dimensions = 1;
    
    row1_in.signals.values = zeros(n_timesteps, 1);
    row2_in.signals.values = zeros(n_timesteps, 1);
    row3_in.signals.values = zeros(n_timesteps, 1);
    row4_in.signals.values = zeros(n_timesteps, 1);
    
    col1_in.signals.values = zeros(n_timesteps, 1);
    col2_in.signals.values = zeros(n_timesteps, 1);
    col3_in.signals.values = zeros(n_timesteps, 1);
    col4_in.signals.values = zeros(n_timesteps, 1);
    
    row1_in.signals.values(1:size_As(2)) = As(1, 1:end);
    row2_in.signals.values(1:size_As(2)) = As(2, 1:end);
    row3_in.signals.values(1:size_As(2)) = As(3, 1:end);
    row4_in.signals.values(1:size_As(2)) = As(4, 1:end);
    
    for t = 0:n - 1
        col1_in.signals.values(4*t + 1 : 4*t + 4) = Bs(1:end, 4*t + 1);
        col2_in.signals.values(4*t + 1 : 4*t + 4) = Bs(1:end, 4*t + 2);
        col3_in.signals.values(4*t + 1 : 4*t + 4) = Bs(1:end, 4*t + 3);
        col4_in.signals.values(4*t + 1 : 4*t + 4) = Bs(1:end, 4*t + 4); 
    end
end
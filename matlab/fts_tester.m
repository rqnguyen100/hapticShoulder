%% Clear All
clear; clc; close all

%% Define file names
terminal_files = {'Terminal/test2.csv', 'Terminal/test3.csv'};

fts_files = {'FTS/ftest2.csv', 'FTS/ftest3.csv'};


%% No Haptics

% Read the terminal CSV file
terminal = readtable(terminal_files{1});

% Get terminal time data
t_time_data = terminal(:,"TimeAfterStart_up_ms_");
t_time = table2array(t_time_data);
t_time = t_time / 1000; % convert from milliseconds to seconds
t_time = t_time(361:end); % manual synchronization
t_time = t_time - t_time(1); % calibrate to start at 0

% Get mujBig position data
mujBig_pos_data = terminal(:,"MUJBigBasketPosition_deg_");
mujBig_pos = table2array(mujBig_pos_data);
mujBig_pos = mujBig_pos(361:end); % manual synchronization

% Get mujSmall position data
mujSmall_pos_data = terminal(:,"MUJSmallBasketPosition_deg_");
mujSmall_pos = table2array(mujSmall_pos_data);
mujSmall_pos = mujSmall_pos(361:end); % manual synchronization

% Get separJ position data
separJ_pos_data = terminal(:,"SeparateJointPosition_deg_");
separJ_pos = table2array(separJ_pos_data);
separJ_pos = separJ_pos(361:end); % manual synchronization


%------------------------------------%

% Read the FTS CSV file
fts = readtable(fts_files{1});

% Get FTS time data in seconds
f_time_data = fts(:,"Time");
f_time = table2array(f_time_data);
f_time = seconds(f_time); % converts from duration to double
f_time1 = f_time - f_time(1); % calibrate to start at 0

% Get force data in N
fx_data = fts(:,"Fx"); fy_data = fts(:,"Fy"); fz_data = fts(:,"Fz"); 
fx = table2array(fx_data); fy = table2array(fy_data); fz = table2array(fz_data);
f_mag = (fx.^2 + fy.^2 + fz.^2).^(1/2);

% Get torque data in Nm
tx_data = fts(:,"Tx"); ty_data = fts(:,"Ty"); tz_data = fts(:,"Tz"); 
tx = table2array(tx_data); ty = table2array(ty_data); tz = table2array(tz_data); 
t_mag = (tx.^2 + ty.^2 + tz.^2).^(1/2);

% Filter fz data with nth-order butterworth lpf with cutoff of fc Hz 
fc = 5; n = 3;
fs = 125; nyq = fs/2;

[b,a] = butter(n,fc/nyq);
f_mag = filtfilt(b,a,f_mag);
t_mag = filtfilt(b,a,t_mag);

%------------------------------------%

figure(1)

subplot(3,1,1);
sgtitle("No Haptics")
plot(t_time, mujBig_pos); hold on; plot(t_time, mujSmall_pos); plot(t_time, separJ_pos);
xlabel("Time (s)"); ylabel("Angle (deg)");
legend(["Big Basket" "Small Basket" "Separate"],"Location","best")

subplot(3,1,2)
plot(f_time1, f_mag)
xlabel("Time (s)"); ylabel("Force Mag (N)");

subplot(3,1,3)
plot(f_time1, t_mag);
xlabel("Time (s)"); ylabel("Torque Mag (Nm)");


%% Haptics

% Read the terminal CSV file
terminal = readtable(terminal_files{2});

% Get terminal time data
t_time_data = terminal(:,"TimeAfterStart_up_ms_");
t_time = table2array(t_time_data);
t_time = t_time / 1000; % convert from ms to s
t_time = t_time(712:end); % manual synchronization
t_time = t_time - t_time(1); % calibrate to start at 0

% Get mujBig position data
mujBig_pos_data = terminal(:,"MUJBigBasketPosition_deg_");
mujBig_pos = table2array(mujBig_pos_data);
mujBig_pos = mujBig_pos(712:end); % manual synchronization

% Get mujSmall position data
mujSmall_pos_data = terminal(:,"MUJSmallBasketPosition_deg_");
mujSmall_pos = table2array(mujSmall_pos_data);
mujSmall_pos = mujSmall_pos(712:end); % manual synchronization

% Get separJ position data
separJ_pos_data = terminal(:,"SeparateJointPosition_deg_");
separJ_pos = table2array(separJ_pos_data);
separJ_pos = separJ_pos(712:end); % manual synchronization


%------------------------------------%

% Read the FTS CSV file
fts = readtable(fts_files{2});

% Get FTS time data in seconds
f_time_data = fts(:,"Time");
f_time = table2array(f_time_data);
f_time = seconds(f_time); % converts from duration to double
f_time = f_time(2053:end); % manual synchronization
f_time2 = f_time - f_time(1); % calibrate to start at 0

% Get force data in N
fx_data = fts(:,"Fx"); fy_data = fts(:,"Fy"); fz_data = fts(:,"Fz"); 
fx = table2array(fx_data); fy = table2array(fy_data); fz = table2array(fz_data);
fx = fx(2053:end); fy = fy(2053:end); fz = fz(2053:end); % manual synchronization
f_mag2 = (fx.^2 + fy.^2 + fz.^2).^(1/2);

% Get torque data in Nm
tx_data = fts(:,"Tx"); ty_data = fts(:,"Ty"); tz_data = fts(:,"Tz"); 
tx = table2array(tx_data); ty = table2array(ty_data); tz = table2array(tz_data); 
tx = tx(2053:end); ty = ty(2053:end); tz = tz(2053:end); % manual synchronization
t_mag2 = (tx.^2 + ty.^2 + tz.^2).^(1/2); 

% Filter fz data with nth-order butterworth lpf with cutoff of fc Hz 
fc = 5; n = 3;
fs = 125; nyq = fs/2;

[b,a] = butter(n,fc/nyq);
f_mag2 = filtfilt(b,a,f_mag2);
t_mag2 = filtfilt(b,a,t_mag2);

%------------------------------------%

figure(2)

subplot(3,1,1);
sgtitle("Haptics")
plot(t_time, mujBig_pos); hold on; plot(t_time, mujSmall_pos); plot(t_time, separJ_pos);
xlabel("Time (s)"); ylabel("Angle (deg)");
legend(["Big Basket" "Small Basket" "Separate"],"Location","best")

subplot(3,1,2)
plot(f_time2, f_mag2)
xlabel("Time (s)"); ylabel("Force Mag (N)");

subplot(3,1,3)
plot(f_time2, t_mag2);
xlabel("Time (s)"); ylabel("Torque Mag (Nm)");

%% Comparison
% manual synchronization to start at same time and overlap

figure(3)

f_time1 = f_time1(227:end);
f_time1 = f_time1 - f_time1(1);

f_mag = f_mag(227:end);
f_mag = f_mag - f_mag(1);

t_mag = t_mag(227:end);
t_mag = t_mag - t_mag(1);

f_max = max(f_mag); f2_max = max(f_mag2);
t_max = max(t_mag); t2_max = max(t_mag2);

%%

figure(3)
plot(f_time1(1:2900), f_mag(1:2900)); % manual synchronization
title("Force Magnitude")
hold on;
plot(f_time2(1:2900), f_mag2(1:2900)); % manual synchronization

yl = yline(f_max, "b--", string(f_max));
yl.LabelHorizontalAlignment = "right";
yl.LabelVerticalAlignment = 'bottom';
yl2 = yline(f2_max, "r--", string(f2_max));
yl2.LabelHorizontalAlignment = "left";
yl2.LabelVerticalAlignment = 'top';

xl = xline(9.031,"k-.","haptics enabled");
xl.LabelVerticalAlignment = 'middle';
xl.LabelHorizontalAlignment = 'left';
ylim([0 12])

xlabel("Time (s)"); ylabel("Force Magnitude (N)");
legend(["No Haptics" "Haptics"],"Location","southeast");

%-----%

figure(4)
plot(f_time1(1:2900), t_mag(1:2900)); % manual synchronization
title("Torque Magnitude")
hold on;
plot(f_time2(1:2900), t_mag2(1:2900)); % manual synchronization

yl = yline(t_max, "b--", string(t_max));
yl.LabelHorizontalAlignment = "right";
yl.LabelVerticalAlignment = 'bottom';
yl2 = yline(t2_max, "r--", string(t2_max));
yl2.LabelHorizontalAlignment = "left";
yl2.LabelVerticalAlignment = 'top';

xl = xline(9.031,"k-.","haptics enabled");
xl.LabelVerticalAlignment = 'middle';
xl.LabelHorizontalAlignment = 'left';
ylim([0 1.6]);

xlabel("Time (s)"); ylabel("Torque Magnitude (Nm)");
legend(["No Haptics" "Haptics"],"Location","southeast");

%Note: when plotting, change the variable P to the absolute path to the
%project folder that exists on your computer
P = 'C:\Users\sahan\Documents\ASTE499\ASTE499-FinalProject\';
S = plotResults(P);

for k = 1:numel(S)
    figure(k)
    hold on
    subplot(2,2,1)
    plot(S(k).data(:,1), S(k).data(:,2));
    xlabel('Time')
    ylabel('Acceleration')
    
    subplot(2,2,2)
    plot(S(k).data(:,1), S(k).data(:,3));
    xlabel('Time')
    ylabel('Velocity')
    
    subplot(2,2,3)
    plot(S(k).data(:,1), S(k).data(:,4));
    xlabel('Time')
    ylabel('Altitude')
end

function structure = plotResults(P)
S = dir(fullfile(P,'*.csv')); 
structure = struct();
for k = 1:numel(S)
    F = fullfile(P,S(k).name);
    %structure(k).data = readtable(F, 'NumHeaderLines', 1);
    structure(k).data = readmatrix(F);
end

end

%% initialization
clear all;close all;clc; %#ok<CLALL>                                       % cleaning the Workspace and Command Windows
file_name='test_121720_2_9points_elastic_bands_variable_force';            % the data file name
data = importdata(strcat(file_name,'.txt'));    % importing the data
%data = importdata('C:\Users\dario\Documents\Github\Cat_skin\Code\code_Ali_V1\code_Ali_V1\test_121720_2_elasticBands_blackMass_randomF.txt');
donwsampling_rate = 25;                                                    % the downsampling rate
downsampled_data = downsample(data,donwsampling_rate);                     % downsampling the data
donwsampled_and_labeled_data =...
    zeros(floor(size(data,1)/donwsampling_rate), size(data,2)+1);          % pre-alocating donwsampled_and_labeled_data
repeated_labels=repmat(1:9,1,ceil(size(downsampled_data,1)/9));            % generaqting labels
donwsampled_and_labeled_data(:,1:end-1)=downsampled_data;                  % downsampling the data
labels=repeated_labels(1:size(downsampled_data,1));                        % selecting labels consistent to the lenght of the recording
donwsampled_and_labeled_data(:,end)=labels;                                % assigning the labels to the downsampled data
%% plotting and savingthe processed data
figure(); plot(donwsampled_and_labeled_data(:,1:4))                        % plotting sensor readings
legend(...
    'Sensor 1','Sensor 2','Sensor 3','Sensor 4', 'location', 'southeast')  % setting the plot legend
csvwrite(file_name,donwsampled_and_labeled_data)                           % writing the preprocessed data into a csv file
%% KNN classification
rng(100)                                                                   % setting the random seed to a constant to have consistencu across results; can do a cross-validation for the final results
K=4;                                                                       % setting K in KNN; number of nearest neighbors to be participated in the voting
test_percentage=.8;                                                        % setting the test/train ratio
[train_data,test_data] = dividerand(donwsampled_and_labeled_data',...
    test_percentage, 1-test_percentage);                                   % randomized test, train split
mdl=fitcknn(train_data(1:4,:)',train_data(5,:)','NumNeighbors',K);         % fitting the KNN model
KNNPred=predict(mdl,test_data(1:4,:)');                                    % running the KNN model on the test data
accuracy=sum((KNNPred-test_data(end,:)')==0)/length(KNNPred);              % calculating the accuracy on the test set
disp(['accuracy is ', num2str(100*accuracy), '%'])                         % displaying accuracy percentage on the Command Window
%% plotting classification results
alpha_value = .5;                                                          % transparency of plot lines
plot(test_data(end,:)','color',[0, 0.4470, 0.7410, alpha_value],...
    'linewidth',3);hold on;                                                % plotting the test results
plot(KNNPred,'color',[0.8500, 0.3250, 0.0980, alpha_value],'linewidth',2); % plotting the test results
legend('test labels','predicted labels')                                   % test result legends
plotconfusion(categorical(test_data(end,:)'),categorical(KNNPred))         % plotting the confusion matrix

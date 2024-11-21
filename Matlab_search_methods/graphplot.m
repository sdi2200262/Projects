function graphplot(x, f1, f2)
    
    % Evaluate the functions
    y1 = f1(x);
    y2 = f2(x);

    % Create the plot
    figure;
    plot(x, y1, 'b-', 'LineWidth', 1.5); hold on; % Plot f1
    plot(x, y2, 'r--', 'LineWidth', 1.5); % Plot f2
    
    yline(0, 'k--', 'LineWidth', 1); % Horizontal line at y = 0

    xlabel('x');
    ylabel('y');
    title('Graphs of f_1(x) and f_2(x)');
    legend('f_1(x)', 'f_2(x)', 'y = 0', 'Location', 'best');
    grid on;

    axis tight;
end

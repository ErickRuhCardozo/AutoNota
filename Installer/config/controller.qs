function Controller()
{

}

Controller.prototype.IntroductionPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.TargetDirectoryPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.LicenseCheckPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.StartMenuSelectionPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.StartMenuDirectoryPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function()
{
    gui.clickButton(buttons.CommitButton);
}

Controller.prototype.PerformInstallationPageCallback = function()
{
    gui.clickButton(buttons.CommitButton);
}

Controller.prototype.FinishedPageCallback = function()
{
    gui.clickButton(buttons.CommitButton);
}

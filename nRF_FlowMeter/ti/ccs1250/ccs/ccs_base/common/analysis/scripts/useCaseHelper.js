//
var Integer = Java.type("java.lang.Integer");
var Long    = Java.type("java.lang.Long");
var System  = Java.type("java.lang.System");
//
var File = Java.type("java.io.File");
//
var ActivityManager = Java.type("com.ti.dvt.control.engine.activities.ActivityManager");
var IActivity       = Java.type("com.ti.dvt.control.engine.activities.IActivity");
//
var Configure              = Java.type("com.ti.dvt.control.engine.types.Configure");
var ConfigAnalysisFeatures = Java.type("com.ti.dvt.control.engine.types.ConfigAnalysisFeatures");
var ConfigButton           = Java.type("com.ti.dvt.control.engine.types.ConfigButton");
var ConfigCheck            = Java.type("com.ti.dvt.control.engine.types.ConfigCheck");
var ConfigCombo            = Java.type("com.ti.dvt.control.engine.types.ConfigCombo");
var ConfigEdit             = Java.type("com.ti.dvt.control.engine.types.ConfigEdit");
var ConfigFile             = Java.type("com.ti.dvt.control.engine.types.ConfigFile");
var ConfigLabel            = Java.type("com.ti.dvt.control.engine.types.ConfigLabel");
var ConfigMessage          = Java.type("com.ti.dvt.control.engine.types.ConfigMessage");
var ConfigRow              = Java.type("com.ti.dvt.control.engine.types.ConfigRow");
var ConfigSection          = Java.type("com.ti.dvt.control.engine.types.ConfigSection");
var ConfigShell            = Java.type("com.ti.dvt.control.engine.types.ConfigShell");
var ConfigTable            = Java.type("com.ti.dvt.control.engine.types.ConfigTable");
var ConfigWizard           = Java.type("com.ti.dvt.control.engine.types.ConfigWizard");
var ConfigWizardPage       = Java.type("com.ti.dvt.control.engine.types.ConfigWizardPage");
var IRun                   = Java.type("com.ti.dvt.control.engine.types.IRun");
var Status                 = Java.type("com.ti.dvt.control.engine.types.Status");
//
var ConfigBusyProgress = Java.type("com.ti.dvt.analysis.suite.ConfigBusyProgress");
var ConfigProperty     = Java.type("com.ti.dvt.analysis.suite.ConfigProperty");
//
var IDEAdapterManager = Java.type("com.ti.dvt.ideadapter.IDEAdapterManager");

//
var SystemAnalyzerUseCaseHelper = Java.type("com.ti.dvt.analysis.suite.usecasehelpers.SystemAnalyzerUseCaseHelper");
var TraceUseCaseHelper          = Java.type("com.ti.dvt.analysis.suite.usecasehelpers.TraceUseCaseHelper");

var Runnable = Java.type("java.lang.Runnable"); 

var dvt_reset = null;
var saveProgress = null;
var logger = null;
function dvt_usecase_launch_dialog()
{
	//TODO: Multiple contributors.
	var wizardDialog = new ConfigWizard("Analysis Configuration");
	var wizardPage = new ConfigWizardPage(dvt_activity.getName() + " Configuration", dvt_activity.getDescription());
	wizardDialog.addPage(wizardPage);

	var resetButton = new ConfigButton("Reset To Original Settings");
	resetButton.setIcon("platform:/plugin/com.ti.dvt.control.gui/icons/reset.gif");
	if (dvt_reset != null && dvt_reset instanceof IRun)
	{
//try{
//p_sa_uc_helper.breakPoint();
//resetButton.addRun(new IRun({run: function() {resetConfig(wizardDialog)}}));
var MyRunnable = Java.extend(Runnable, { 
	run: function() { 
		//p_sa_uc_helper.traceMsg("WOW!");
		resetConfig(wizardDialog);
    	} 
}); 
resetButton.addRun(new MyRunnable());
//}
//catch( e ){
//  p_sa_uc_helper.traceMsg( e.message );
//  p_sa_uc_helper.traceMsg(new Error().stack);
//  p_sa_uc_helper.traceMsg( e.stack);
//}
	}
	else
	{
		resetButton.setEnabled(false);
	}
	wizardDialog.addButton(resetButton);

	var saveButton = new ConfigButton("Save this configuration");
	saveButton.setIcon("platform:/plugin/com.ti.dvt.analysis.suite.gui/icons/save.gif");
	//saveButton.addRun(new IRun({run: function() {dvt_activity.saveAs();}}));
var MyRunnable = Java.extend(Runnable, { 
    	run: function() { 
		dvt_activity.saveAs();
    	} 
}); 
saveButton.addRun(new MyRunnable());
	wizardDialog.addButton(saveButton);
	
	if (dvt_activity.getPriority() >= IActivity.DVT_CUSTOM_SAVE_START)
	{
		var deleteButton = new ConfigButton("Delete");
		deleteButton.setIcon("platform:/plugin/com.ti.dvt.control.gui/icons/delete_config.gif");
		//deleteButton.addRun(new IRun({run: function() {wizardDialog.cancel();}}));
var MyRunnable = Java.extend(Runnable, {
    	run: function() { 
		wizardDialog.cancel();
    	} 
}); 
deleteButton.addRun(new MyRunnable());
		//deleteButton.addRun(new IRun({run: function() {dvt_activity.deleteSave();}}));
var MyRunnable = Java.extend(Runnable, {
    	run: function() { 
		dvt_activity.deleteSave();
    	} 
}); 
deleteButton.addRun(new MyRunnable());
		wizardDialog.addButton(deleteButton);
		
		var exportButton = new ConfigButton("Export Configuration...");
		exportButton.setIcon("platform:/plugin/com.ti.dvt.analysis.suite.gui/icons/solution_saveas.gif");
		//exportButton.addRun(new IRun({run: function() {dvt_activity.exportSave();}}));
var MyRunnable = Java.extend(Runnable, {
    	run: function() { 
		dvt_activity.exportSave();
    	} 
}); 
exportButton.addRun(new MyRunnable());
		wizardDialog.addButton(exportButton);
	}


	var configTable = new ConfigTable();
	wizardPage.addWidget(configTable);
	configTable.setSpanAllColumns(true);

	/*
	var removeButton = new ConfigButton("Remove Table");
	removeButton.setIcon("platform:/plugin/com.ti.dvt.analysis.suite.gui/icons/delete_all.gif");
	removeButton.addRun(new IRun({run: function() {configTable.setRemoved(!configTable.getRemoved());wizardDialog.refresh();}}));
	wizardDialog.addButton(removeButton);
	*/

	var launch = new Object();
	launch.execute = function() {wizardDialog.execute();}
	launch.refresh = function() {wizardDialog.refresh();}
	launch.dialog = wizardDialog;
	launch.page = wizardPage; 
	launch.table = configTable;
	launch.reset = resetButton;
	

	return launch;
}

function resetConfig(wizardDialog)
{
	var warning = new ConfigMessage("This will restore original settings. Do you want to continue?");
	warning.setIcon(ConfigMessage.WARNING);
	var buttons = ["OK","Cancel"];
	warning.setTitle("Reset Warning");
	warning.setButtons(buttons);
	warning.execute();
	
	if (warning.getResult().equals("OK"))
	{
		wizardDialog.cancel();
		dvt_activity.restoreDefault();
	}
}

function addConfigurationButtons()
{
	//Add configuration buttons to Analysis Dashboard column.
	/*
	var configure = new Configure();
	var propertiesButton = new ConfigButton("Analysis Properties...");
	propertiesButton.setIcon("platform:/plugin/com.ti.dvt.analysis.suite.gui/icons/properties.gif");
	var propertyRun = { run: function() { applyWhenRunning(); } };
	propertiesButton.addRun(new IRun(propertyRun));
	configure.addWidget(propertiesButton);
	dvt_activity.addConfigure(configure);
	*/

	var status = new Status();
	var button = new ConfigButton("Close Session", "delete.gif");
	//button.addRun(new IRun(propertyRun));
var MyRunnable = Java.extend(Runnable, {
	run: function() { 
		dvt_activity.removeFromSession();
	} 
}); 
button.addRun(new MyRunnable());
	status.addWidget(button);
	dvt_activity.addStatus(status);
	
	return;/* propertiesButton;*/
}

function getDataProviderList()
{
	dataprovider_list = dataproviders.split(",");

	if(dataprovider_list.length > 1)
	{
		//TODO right now assuming only one DataProvider and AF list
		logger.traceMsg("Do not support more than one Data Provider per UC");
		var message = new ConfigMessage("Do not support more than one Data Provider per UC");
		message.setIcon(ConfigMessage.ERROR);
		message.execute();
		dvt_activity_resources = "";  //Note this is needed here because the removeFromSession is asynch
		dvt_activity.removeFromSession();
		return;
	}
	
	return dataprovider_list;
}

function findAnalysisFeatures(dataprovider)
{
	var analysisFeatures = java.util.ArrayList();
	
	var afs = eval(dataprovider+"_analyzer").split(",");
	for(af=0;af<afs;af++)
	{
		//TODO trim()
		logger.traceMsg("DP " + dataprovider + " <-- " + afs[af]);
		//Add AFs
		var analysisFeatureTemplate = ActivityManager.get().findAction(afs[af]);
		if (analysisFeatureTemplate != null)
		{
			analysisFeatures.add(analysisFeatureTemplate);
		}
		else
		{
			logger.traceMsg("Could not find analysis feature " + afs[af]);
		}
	}
	
	return analysisFeatures;
}

function addAnalysisFeatures(dataproviderActivity, analysisFeatures)
{
	for(af in analysisFeatures)
	{
		//Launch AFs
		var analysisFeature = ActivityManager.get().addActionToSession(dataproviderActivity, af);
	}
}
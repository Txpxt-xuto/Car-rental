function doGet(){
    return HtmlService.createTemplateFromFile('index').evaluate()
    .setTitle('Epic Coding Channel')
    .setFaviconUrl('https://cdn.jsdelivr.net/gh/EPICCODING17/image/Logo-EicCoding.png')
    .addMetaTag('viewport', 'width=device-width, initial-scale=1')
    .setXFrameOptionsMode(HtmlService.XFrameOptionsMode.ALLOWALL)
}

function include(filename){
    return HtmlService.createHtmlOutputFromFile(filename).getContent()
}
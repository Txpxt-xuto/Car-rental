#pragma once

#include <system/object.h>
#include <system/array.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object_ext.h>
#include <system/exceptions.h>
#include <system/environment.h>
#include <system/diagnostics/trace.h>
#include <system/console.h>
#include <MailMessage.h>
#include <EmlLoadOptions.h>
#include <Clients/Smtp/SmtpClient/SmtpClient.h>
#pragma once

#include <Clients/SecurityOptions.h>
#include <system/io/path.h>
#include <system/io/directory_info.h>
#include <system/io/directory.h>
#include <Licensing/License.h>


using namespace Aspose::Email::Clients::Smtp;
using namespace Aspose::Email::Clients;
using namespace Aspose::Email;
using namespace System;

void SendingEMLWithSMTP()
{
    // Set the license for Aspose.Email for CPP
    SharedPtr<License> license = System::MakeObject<License>();
    license->SetLicense(u"licFile");

    // The path to the source EML file to be send
    System::String dstEmail = u"Message.eml";
    
    // Ue MailMessage class to load the email Message from disk
    System::SharedPtr<MailMessage> message = System::MakeObject<MailMessage>();
    
    // Load the file in EML format
    message = MailMessage::Load(dstEmail, System::MakeObject<EmlLoadOptions>());
    
    // Instantiate SmtpClient class object to connect to SMTP server
    System::SharedPtr<SmtpClient> client = System::MakeObject<SmtpClient>(u"smtp.gmail.com", 587, 
        u"your.email@gmail.com", u"your.password");
    client->set_SecurityOptions(Aspose::Email::Clients::SecurityOptions::Auto);
    
    try
    {
        // Send the message
        client->Send(message);
        System::Console::WriteLine(u"Message has been sent");
    }
    catch (System::Exception& ex)
    {
        System::Diagnostics::Trace::WriteLine(System::ObjectExt::ToString(ex));
    }
    
    System::Console::WriteLine(System::Environment::get_NewLine() + u"Email sent using EML file successfully. " + dstEmail);
}
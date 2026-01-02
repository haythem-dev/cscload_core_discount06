using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Mail;

namespace PHOENIXUtil
{
    /// <summary>
    /// 
    /// </summary>
    public class Mail
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="ipSmtpServer"></param>
        /// <param name="fromAddress"></param>
        /// <param name="recipientsAddress"></param>
        /// <param name="subject"></param>
        /// <param name="body"></param>
        /// <param name="attachmentFileAddress"></param>
        /// <param name="priority"></param>
        /// <param name="port"></param>
        public static void sendMailWithoutAuth(ref string ipSmtpServer, ref string fromAddress, ref string[] recipientsAddress, ref string subject, ref string body, string attachmentFileAddress = null, MailPriority priority = MailPriority.Normal, int port = 25)
        {
            try
            {                
                MailMessage mail = new MailMessage();
                mail.Subject = subject;
                mail.Body = body;
                mail.From = new System.Net.Mail.MailAddress(fromAddress);
                mail.Priority = priority;
                if (attachmentFileAddress != null)
                {                    
                    mail.Attachments.Add(new System.Net.Mail.Attachment(attachmentFileAddress));
                }
                foreach (string recipient in recipientsAddress) mail.Bcc.Add(recipient);

                SmtpClient smtp = new SmtpClient(ipSmtpServer, port);
                                
                smtp.Send(mail);                
            }
            catch (Exception Ex)
            {
                throw Ex;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="ipSmtpServer"></param>
        /// <param name="fromAddress"></param>
        /// <param name="recipientsAddress"></param>
        /// <param name="subject"></param>
        /// <param name="body"></param>
        /// <param name="authLogin"></param>
        /// <param name="authPW"></param>
        /// <param name="attachmentFileAddress"></param>
        /// <param name="priority"></param>
        /// <param name="port"></param>
        public static void sendMailWithAuth(ref string ipSmtpServer, ref string fromAddress, ref string[] recipientsAddress, ref string subject, ref string body, ref string authLogin, ref string authPW, string attachmentFileAddress = null, MailPriority priority = MailPriority.Normal, int port = 25)
        {
            try
            {
                MailMessage mail = new MailMessage();
                System.Net.Mail.Attachment att = null;
                mail.Subject = subject;
                mail.Body = body;
                mail.From = new System.Net.Mail.MailAddress(fromAddress);
                mail.Priority = priority;
                
                if (attachmentFileAddress != null) att = new System.Net.Mail.Attachment(attachmentFileAddress);
                foreach (string recipient in recipientsAddress) mail.Bcc.Add(recipient);

                SmtpClient smtp = new SmtpClient(ipSmtpServer, port);
                smtp.Credentials = new System.Net.NetworkCredential(authLogin, authPW);
                
                smtp.Send(mail);
            }
            catch (Exception Ex)
            {
                throw Ex;
            }   
        }        
    }
}

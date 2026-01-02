using System;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using System.Xml;
using System.Xml.Schema;
using System.Xml.XPath;
using System.Collections.Generic;

namespace Covid19XmlViewerBatch
{
	/// <summary>
	/// XML utilities
	/// </summary>
	public static class XML
	{
		/// <summary>
		///
		/// </summary>
		/// <param name="xmlfile"></param>
		/// <param name="xpathquery"></param>
		/// <returns></returns>
		public static XPathNodeIterator getNodeIteratorForXPathQuery(string xmlfile, string xpathquery)
		{
			XPathDocument xpdoc = new XPathDocument(xmlfile);
			XPathNavigator xpnavi = xpdoc.CreateNavigator();
			return xpnavi.Select(xpathquery);
		}

		/// <summary>
		///
		/// </summary>
		/// <param name="xpnit"></param>
		/// <returns></returns>
		public static List<string> getValuesFromNodeIterator(XPathNodeIterator xpnit)
		{
			List<string> retval = new List<string>();
			while (xpnit.MoveNext())
			{
				retval.Add(xpnit.Current.Value);
			}
			return retval;
		}

		/// <summary>
		///
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="serialized"></param>
		/// <returns></returns>
		public static T Deserialize<T>(string serialized)
		{
			T deserialisedXML = default(T);
			XmlSerializer serializer = new XmlSerializer(typeof(T));
			FileStream fileHandle = null;
			try
			{
				fileHandle = new FileStream(serialized, FileMode.Open);
			}
			catch (Exception Ex)
			{
				throw Ex;
			}
			XmlReader xmlReader = XmlReader.Create(fileHandle);
			if (serializer.CanDeserialize(xmlReader))
			{
				deserialisedXML = (T)serializer.Deserialize(xmlReader);
			}
			else
			{
				fileHandle.Dispose();
				throw new Exception("File not deserializable");
			}
			fileHandle.Dispose();
			return deserialisedXML;
		}

		/// <summary>
		///
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="toSerialize"></param>
		/// <param name="file"></param>
		public static void Serialize<T>(T toSerialize, string file)
		{
			XmlSerializer serializeXML = new XmlSerializer(typeof(T));
			try
			{
				using (XmlWriter xmlWriter  = XmlWriter.Create(file))
				{
					serializeXML.Serialize(xmlWriter, toSerialize);
				}
			}
			catch (Exception Ex)
			{
				throw Ex;
			}
		}

		/// <summary>
		///
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="stringToDeserialize"></param>
		/// <returns></returns>
		public static T DeSerializeString<T>(string stringToDeserialize)
	    {
		    XmlSerializer serializer = new XmlSerializer(typeof(T));
		    MemoryStream memStream = new MemoryStream(Encoding.UTF8.GetBytes(stringToDeserialize));
		    try
		    {
			    T resultingObjcect = (T)serializer.Deserialize(memStream);
			    return resultingObjcect;
		    }
		    catch (Exception Ex)
		    {
			    throw Ex;
		    }
	    }

        public static T xDeSerialize<T>(string serialized)
        {
            T deserialised = default(T);
            XmlSerializer serializer = new XmlSerializer(typeof(T));
            StringReader stringReader = new StringReader(serialized);
            XmlReader xmlReader = XmlReader.Create(stringReader);

            if (serializer.CanDeserialize(xmlReader))
            {
                deserialised = (T)serializer.Deserialize(xmlReader);
            }
            else
            {
                try
                {
                    deserialised = (T)serializer.Deserialize(xmlReader);
                }
                catch (Exception ex)
                {
                    throw new Exception(String.Format("Deserialize Exception: {0}", ex.Message) );
                }

            }
            return deserialised;
        }

        public static T DeSerializeString<T>(string stringToDeserialize, Encoding enc)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(T));
            MemoryStream memStream = new MemoryStream(enc.GetBytes(stringToDeserialize));
            try
            {
                T resultingObjcect = (T)serializer.Deserialize(memStream);
                return resultingObjcect;
            }
            catch (Exception Ex)
            {
                throw Ex;
            }
        }


		/// <summary>
		///
		/// </summary>
		/// <param name="xmldata"></param>
		/// <param name="xsdfilepath"></param>
		/// <param name="targetns"></param>
		/// <param name="throwexception"></param>
		/// <returns></returns>
		public static bool ValidateXML(string xmldata, string xsdfilepath, string targetns = "", bool throwexception = false )
	    {
		    try
		    {
			    XmlDocument xmldoc = new XmlDocument();
			    xmldoc.LoadXml(xmldata);
			    xmldoc.Schemas.Add(targetns, xsdfilepath);
			    xmldoc.Validate(XML.ValidationEventHandler);
			    return true;
		    }
		    catch (Exception ex)
		    {
			    if (throwexception) throw ex;
			    return false;
		    }
	    }

		/// <summary>
		///
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="args"></param>
		private static void ValidationEventHandler(object sender, ValidationEventArgs args)
	    {
	    }

        /// <summary>
        /// indent a XML string
        /// </summary>
        /// <param name="xml">xml string</param>
        /// <returns>indented xml string</returns>
        public static string IndentXMLString(string xml)
        {
            MemoryStream ms = new MemoryStream();
            XmlTextWriter xtw = new XmlTextWriter(ms, Encoding.Unicode);
            XmlDocument doc = new XmlDocument();
            try
            {
                doc.LoadXml(xml); // Load the unformatted XML text string into an instance of the XML Document Object Model (DOM)
                xtw.Formatting = Formatting.Indented; // Set the formatting property of the XML Text Writer to indented the text writer is where the indenting will be performed
                doc.WriteContentTo(xtw); // write dom xml to the xmltextwriter
                xtw.Flush(); // Flush the contents of the text writer to the memory stream, which is simply a memory file
                ms.Seek(0, SeekOrigin.Begin); // set to start of the memory stream (file)
                StreamReader sr = new StreamReader(ms); // create a reader to read the contents of the memory stream (file)
                return sr.ReadToEnd(); // return the formatted string to caller
            }
            catch
            {
                return string.Empty;
            }
        }



	} // class XML

} // namespace PHOENIXUTIL



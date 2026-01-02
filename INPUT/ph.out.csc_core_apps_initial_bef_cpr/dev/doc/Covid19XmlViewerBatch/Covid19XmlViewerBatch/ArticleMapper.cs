using System;
using System.Collections.Generic;
using System.IO;

namespace Covid19XmlViewerBatch
{
    public class ArticleMapper
    {                
        public List<int> ArticleNumbers { get; private set; }

        public void MapArticles(string articleid, string articleMappingFile = "ArtikelMapping.xml")
        {
            ArticleNumbers = new List<int>();            
            ArtikelMapping artMapping = XML.DeSerializeString<ArtikelMapping>(File.ReadAllText(articleMappingFile));
            foreach( ArtikelMappingXMLArtikel x in artMapping.XMLArtikel)
            {
                if( x.ArticleID.Trim().ToLower() == articleid.Trim().ToLower() )
                {
                    foreach (var artNumber in x.ArtikelNr)
                    {
                        ArticleNumbers.Add(artNumber);
                    }
                }
            }            
        }
    }
}

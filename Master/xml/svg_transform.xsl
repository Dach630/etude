<?xml version="1.0" ?>
<xsl:stylesheet version="1.0" 
		xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
		xmlns="http://www.w3.org/2000/svg"
		>
    <xsl:output
      method="xml"
      indent="yes"
      media-type="image/svg" />
    <xsl:key name="node" match="data/node" use="@id" />
    <xsl:param name="tree"/>
    <xsl:template match="root">
        <svg xmlns="http://www.w3.org/2000/svg" width="100%" height="100%">
            <xsl:call-template name="test">
                <xsl:with-param name="node" select="tree/node"/>
            </xsl:call-template>
        </svg>
    </xsl:template>
    <xsl:template name="test">
        
    </xsl:template>
</xsl:stylesheet>

<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:template match="/project">
        <html>
            <head>
                <title>GC Project - <xsl:value-of select="@name" /></title>
            </head>
            <body>
                <table bgcolor="#00FF00" width="100%" border="0" cellspacing="0" cellpadding="0">
                    <caption><b>Project Name: <xsl:value-of select="@name" /></b></caption>
                    <!-- CONFIG -->
                    <tr>
                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                            <caption><b>Config</b></caption>
                            <tr>
                                <td width="10%">Author</td>
                                <td><xsl:value-of select="config/author" /></td>
                            </tr>
                            <tr>
                                <td>Description</td>
                                <td><xsl:value-of select="config/description" /></td>
                            </tr>
                            <tr>
                                <td>Exported Filename</td>
                                <td><xsl:value-of select="config/file" /></td>
                            </tr>
                            <tr>
                                <td>Encryption Key</td>
                                <td><xsl:value-of select="config/key" /></td>
                            </tr>
                            <tr>
                                <td>Resources Directory</td>
                                <td><xsl:value-of select="config/resources" /></td>
                            </tr>
                            <tr>
                                <td>Groups</td>
                                <td bgcolor="#00FF00">
                                    <xsl:for-each select="config/groups/group">
                                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                                            <caption><b><xsl:value-of select="@name" /></b></caption>
                                            <tr>
                                                <td width="25%">Encrypt</td>
                                                <td><xsl:value-of select="@encrypt" /></td>
                                            </tr>
                                            <tr>
                                                <td>Zip</td>
                                                <td>
                                                    <tr>
                                                        <td width="50%"><b>Type:</b></td><td width="50%"><xsl:value-of select="zip/@type" /></td>
                                                    </tr>
                                                    <tr>
                                                        <td><b>Mask:</b></td><td><xsl:value-of select="zip/@mask" /></td>
                                                    </tr>
                                                </td>
                                            </tr>
                                            <tr>
                                                <td>Directories</td>
                                                <td bgcolor="#00FF00">
                                                    <xsl:for-each select="directories/directory">
                                                        <table width="100%" bgcolor="#33CC33" border="0" cellspacing="0" cellpadding="0">
                                                            <caption><b><xsl:value-of select="@name" /></b></caption>
                                                            <tr>
                                                                <td>
                                                                    <xsl:for-each select="directory">
                                                                        <table width="100%" bgcolor="#66CC66" border="0" cellspacing="0" cellpadding="0">
                                                                        <caption>...<xsl:value-of select="@name" /></caption>
                                                                        <tr>
                                                                            <center>
                                                                                <xsl:if test="directory">
                                                                                    ......
                                                                                </xsl:if>
                                                                            </center>
                                                                        </tr>
                                                                        </table>
                                                                    </xsl:for-each>
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </xsl:for-each>
                                                </td>
                                            </tr>
                                        </table>
                                    </xsl:for-each>
                                </td>
                            </tr>
                        </table>
                    </tr>
                    <tr bgcolor="#FFFFFF"><br /></tr>
                    <!-- SPRITES -->
                    <tr>
                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                            <caption><b>Sprites</b></caption>
                            <tr>
                                <td width="10%">Groups</td>
                                <td>
                                    <xsl:for-each select="sprites/groups/group">
                                        <tr>
                                            <td>
                                                <xsl:value-of select="@name" />
                                                <xsl:for-each select="group">
                                                    <tr>
                                                        ---&gt; <xsl:value-of select="@name" />
                                                        <xsl:if test="group">
                                                            (+)
                                                        </xsl:if>
                                                    </tr>
                                                </xsl:for-each>
                                            </td>
                                        </tr>
                                    </xsl:for-each>
                                </td>
                            </tr>
                            <tr>
                                <td>Sprites</td>
                                <td bgcolor="#00FF00">
                                    <xsl:for-each select="sprites/sprite">
                                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                                            <caption><b><xsl:value-of select="@name" /></b></caption>
                                            <tr>
                                                <td width="25%">ID</td>
                                                <td><xsl:value-of select="@id" /></td>
                                            </tr>
                                            <tr>
                                                <td>File</td>
                                                <td><xsl:value-of select="config/file/@name" /></td>
                                            </tr>
                                            <tr>
                                                <td>Dimensions</td>
                                                <td>
                                                    <xsl:value-of select="@width" />,<xsl:value-of select="@height" />
                                                </td>
                                            </tr>
                                            <tr>
                                                <td>Pivot Location</td>
                                                <td>
                                                    <xsl:value-of select="config/key/@x" />,<xsl:value-of select="config/key/@y" />
                                                </td>
                                            </tr>
                                            <tr>
                                                <td>Colorkey</td>
                                                <td>
                                                    <tr>
                                                        <td width="50%">
                                                            <b>Use:</b>
                                                        </td>
                                                        <td width="50%">
                                                            <xsl:value-of select="config/key/@use" />
                                                        </td>
                                                    </tr>
                                                    <tr>
                                                        <td width="50%">
                                                            <b>Location:</b>
                                                        </td>
                                                        <td width="50%">
                                                            <xsl:value-of select="config/key/@x" />,<xsl:value-of select="config/key/@y" />
                                                        </td>
                                                    </tr>
                                                </td>
                                            </tr>
                                            <tr>
                                                <td>Group</td>
                                                <td><xsl:value-of select="@group" /></td>
                                            </tr>
                                            <tr>
                                                <td>Release Group</td>
                                                <td><xsl:value-of select="release/group" /></td>
                                            </tr>
                                            <tr>
                                                <td>Images</td>
                                                <td bgcolor="#00FF00">
                                                    <xsl:for-each select="images/image">
                                                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                                                            <caption><b>Image <xsl:value-of select="@id" /></b></caption>
                                                            <tr>
                                                                <td width="25%">
                                                                    Location
                                                                </td>
                                                                <td>
                                                                    <xsl:value-of select="@x" />,<xsl:value-of select="@y" />
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </xsl:for-each>
                                                </td>
                                            </tr>
                                        </table>
                                    </xsl:for-each>
                                </td>
                            </tr>
                        </table>
                    </tr>
                    <tr bgcolor="#FFFFFF"><br /></tr>
                    <!-- OBJECTS -->
                    <tr>
                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                            <caption><b>Objects</b></caption>
                            <tr>
                                <td width="10%">Groups</td>
                                <td>
                                    <xsl:for-each select="objects/groups/group">
                                        <tr>
                                            <td>
                                                <xsl:value-of select="@name" />
                                                <xsl:for-each select="group">
                                                    <tr>
                                                        ---&gt; <xsl:value-of select="@name" />
                                                        <xsl:if test="group">
                                                            (+)
                                                        </xsl:if>
                                                    </tr>
                                                </xsl:for-each>
                                            </td>
                                        </tr>
                                    </xsl:for-each>
                                </td>
                            </tr>
                            <tr>
                                <td>Objects</td>
                                <td bgcolor="#00FF00">
                                    <xsl:for-each select="objects/object">
                                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                                            <caption><b><xsl:value-of select="@name" /></b></caption>
                                            <tr>
                                                <td width="25%">ID</td>
                                                <td><xsl:value-of select="@id" /></td>
                                            </tr>
                                            <tr>
                                                <td>Group</td>
                                                <td><xsl:value-of select="@group" /></td>
                                            </tr>
                                            <tr>
                                                <td>Events</td>
                                                <td bgcolor="#00FF00">
                                                    <xsl:for-each select="events/event">
                                                        <table width="100%" bgcolor="#99FF99" border="0" cellspacing="0" cellpadding="0">
                                                            <caption><b><xsl:value-of select="@type" /></b></caption>
                                                            <tr>
                                                                <td>
                                                                    <xsl:value-of select="current()" />
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </xsl:for-each>
                                                </td>
                                            </tr>
                                        </table>
                                    </xsl:for-each>
                                </td>
                            </tr>
                        </table>
                    </tr>
                    <tr bgcolor="#FFFFFF"><br /></tr>
                    <!-- BACKGROUNDS -->
                    <tr>
                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                            <caption><b>Backgrounds</b></caption>
                            <tr>
                                <td width="10%">Groups</td>
                                <td>
                                    <xsl:for-each select="backgrounds/groups/group">
                                        <tr>
                                            <td>
                                                <xsl:value-of select="@name" />
                                                <xsl:for-each select="group">
                                                    <tr>
                                                        ---&gt; <xsl:value-of select="@name" />
                                                        <xsl:if test="group">
                                                            (+)
                                                        </xsl:if>
                                                    </tr>
                                                </xsl:for-each>
                                            </td>
                                        </tr>
                                    </xsl:for-each>
                                </td>
                            </tr>
                            <tr>
                                <td>Backgrounds</td>
                                <td bgcolor="#00FF00">
                                    <xsl:for-each select="backgrounds/background">
                                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                                            <caption><b><xsl:value-of select="@name" /></b></caption>
                                            <tr>
                                                <td width="25%">ID</td>
                                                <td><xsl:value-of select="@id" /></td>
                                            </tr>
                                            <tr>
                                                <td>File</td>
                                                <td><xsl:value-of select="config/file/@name" /></td>
                                            </tr>
                                            <tr>
                                                <td>Dimensions</td>
                                                <td><xsl:value-of select="@width" />,<xsl:value-of select="@height" /></td>
                                            </tr>
                                            <tr>
                                                <td>Colorkey</td>
                                                <td>
                                                    <tr>
                                                        <td width="50%">
                                                            <b>Use:</b>
                                                        </td>
                                                        <td width="50%">
                                                            <xsl:value-of select="config/key/@use" />
                                                        </td>
                                                    </tr>
                                                    <tr>
                                                        <td width="50%">
                                                            <b>Location:</b>
                                                        </td>
                                                        <td width="50%">
                                                            <xsl:value-of select="config/key/@x" />,<xsl:value-of select="config/key/@y" />
                                                        </td>
                                                    </tr>
                                                </td>
                                            </tr>
                                            <tr>
                                                <td>Group</td>
                                                <td><xsl:value-of select="@group" /></td>
                                            </tr>
                                            <tr>
                                                <td>Release Group</td>
                                                <td><xsl:value-of select="release/group" /></td>
                                            </tr>
                                           <tr>
                                                <td>Tileset</td>
                                                <td>
                                                    <tr>
                                                        <td width="50%">
                                                            <b>Use:</b>
                                                        </td>
                                                        <td width="50%">
                                                            <xsl:value-of select="tileset/@use" />
                                                        </td>
                                                    </tr>
                                                    <tr>
                                                        <td width="50%">
                                                            <b>Dimensions:</b>
                                                        </td>
                                                        <td width="50%">
                                                            <xsl:value-of select="tileset/@width" />,<xsl:value-of select="tileset/@height" />
                                                        </td>
                                                    </tr>
                                                    <tr>
                                                        <td width="50%">
                                                            <b>Offset:</b>
                                                        </td>
                                                        <td width="50%">
                                                            <xsl:value-of select="tileset/@xoffset" />,<xsl:value-of select="tileset/@yoffset" />
                                                        </td>
                                                    </tr>
                                                    <tr>
                                                        <td width="50%">
                                                            <b>Spacing:</b>
                                                        </td>
                                                        <td width="50%">
                                                            <xsl:value-of select="tileset/@xspacing" />,<xsl:value-of select="tileset/@yspacing" />
                                                        </td>
                                                    </tr>
                                                </td>
                                            </tr>
                                        </table>
                                    </xsl:for-each>
                                </td>
                            </tr>
                        </table>
                    </tr>
                    <tr bgcolor="#FFFFFF"><br /></tr>
                    <!-- LEVELS -->
                    <tr>
                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                            <caption><b>Levels</b></caption>
                            <tr>
                                <td width="10%">Groups</td>
                                <td>
                                    <xsl:for-each select="levels/groups/group">
                                        <tr>
                                            <td>
                                                <xsl:value-of select="@name" />
                                                <xsl:for-each select="group">
                                                    <tr>
                                                        ---&gt; <xsl:value-of select="@name" />
                                                        <xsl:if test="group">
                                                            (+)
                                                        </xsl:if>
                                                    </tr>
                                                </xsl:for-each>
                                            </td>
                                        </tr>
                                    </xsl:for-each>
                                </td>
                            </tr>
                            <tr>
                                <td>Levels</td>
                                <td bgcolor="#00FF00">
                                    <xsl:for-each select="levels/level">
                                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                                            <caption><b><xsl:value-of select="@name" /></b></caption>
                                            <tr>
                                                <td width="25%">ID</td>
                                                <td><xsl:value-of select="@id" /></td>
                                            </tr>
                                            <tr>
                                                <td>Dimensions</td>
                                                <td>
                                                    <xsl:value-of select="@width" />,<xsl:value-of select="@height" />
                                                </td>
                                            </tr>
                                            <tr>
                                                <td>Group</td>
                                                <td><xsl:value-of select="@group" /></td>
                                            </tr>
                                            <tr>
                                                <td>Start Code</td>
                                                <td><xsl:value-of select="code/start" /></td>
                                            </tr>
                                            <tr>
                                                <td>End Code</td>
                                                <td><xsl:value-of select="code/end" /></td>
                                            </tr>
                                            <tr>
                                                <td>Objects</td>
                                                <td bgcolor="#00FF00">
                                                    <xsl:for-each select="objects/object">
                                                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                                                            <caption><b>Object <xsl:value-of select="@id" /></b></caption>
                                                            <tr>
                                                                <td width="25%">
                                                                    Location
                                                                </td>
                                                                <td>
                                                                    <xsl:value-of select="@x" />,<xsl:value-of select="@y" />
                                                                </td>
                                                            </tr>
                                                            <tr>
                                                                <td>
                                                                    Angle
                                                                </td>
                                                                <td>
                                                                    <xsl:value-of select="@angle" />
                                                                </td>
                                                            </tr>
                                                            <tr>
                                                                <td>
                                                                    Start Code
                                                                </td>
                                                                <td>
                                                                    <xsl:value-of select="start" />
                                                                </td>
                                                            </tr>
                                                            <tr>
                                                                <td>
                                                                    End Code
                                                                </td>
                                                                <td>
                                                                    <xsl:value-of select="end" />
                                                                </td>
                                                            </tr>
                                                        </table>
                                                    </xsl:for-each>
                                                </td>
                                            </tr>
                                        </table>
                                    </xsl:for-each>
                                </td>
                            </tr>
                        </table>
                    </tr>
                    <tr bgcolor="#FFFFFF"><br /></tr>
                    <!-- LOG -->
                    <tr>
                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                            <caption><b>Changelog</b></caption>
                                <tr>
                                    <td width="10%">Date</td>
                                    <td width="10%">Time</td>
                                    <td>Item</td>
                                </tr>
                            <xsl:for-each select="log/changelog/items">
                                <tr>
                                    <td colspan="count(item)">
                                        <xsl:value-of select="@date" />
                                    </td>
                                    <td>
                                        <xsl:for-each select="item">
                                            <tr>
                                                <xsl:value-of select="@time" />
                                            </tr>
                                        </xsl:for-each>
                                    </td>
                                    <td>
                                        <xsl:for-each select="item">
                                            <tr>
                                                <xsl:value-of select="current()" />
                                            </tr>
                                        </xsl:for-each>
                                    </td>
                                </tr>
                            </xsl:for-each>
                        </table>
                    </tr>
                </table>
            </body>
        </html>
    </xsl:template>

    <xsl:template match="/workspace">
        <html>
            <head>
                <title>GC Workspace - <xsl:value-of select="@name" /></title>
            </head>
            <body>
                <table bgcolor="#00FF00" width="100%" border="1" cellspacing="0" cellpadding="0">
                    <caption><b>Workspace Name: <xsl:value-of select="@name" /></b></caption>
                    <!-- PROJECTS -->
                    <tr>
                        <table bgcolor="#00FF00" width="100%" border="1" cellspacing="0" cellpadding="0">
                            <caption><b>Projects</b></caption>
                            <xsl:for-each select="projects/project">
                                <tr>
                                    <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                                        <caption><b>Project <xsl:value-of select="@id" /></b></caption>
                                        <tr>
                                            <td width="25%"><b>Filename:</b></td>
                                            <td><xsl:value-of select="@file" /></td>
                                        </tr>
                                    </table>
                                </tr>
                            </xsl:for-each>
                        </table>
                    </tr>
                    <tr bgcolor="#FFFFFF"><br /></tr>
                    <!-- LOG -->
                    <tr>
                        <table bgcolor="#99FF99" width="100%" border="1" cellspacing="0" cellpadding="0">
                            <caption><b>Changelog</b></caption>
                                <tr>
                                    <td width="10%">Date</td>
                                    <td width="10%">Time</td>
                                    <td>Item</td>
                                </tr>
                            <xsl:for-each select="log/changelog/items">
                                <tr>
                                    <td colspan="count(item)">
                                        <xsl:value-of select="@date" />
                                    </td>
                                    <td>
                                        <xsl:for-each select="item">
                                            <tr>
                                                <xsl:value-of select="@time" />
                                            </tr>
                                        </xsl:for-each>
                                    </td>
                                    <td>
                                        <xsl:for-each select="item">
                                            <tr>
                                                <xsl:value-of select="current()" />
                                            </tr>
                                        </xsl:for-each>
                                    </td>
                                </tr>
                            </xsl:for-each>
                        </table>
                    </tr>
                </table>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>

# pdc


## cambalache

Doc link : https://gitlab.gnome.org/jpu/cambalache
install Flatpak

flatpak run --user ar.xjuan.Cambalache//master



<interface>
  <menu id='menubar'>
    <submenu>
      <attribute name='label' translatable='yes'>_File</attribute>
      <section>
        <item>
          <attribute name='label' translatable='yes'>_New</attribute>
          <attribute name='action'>example.new</attribute>
        </item>
        <item>
          <attribute name='label' translatable='yes'>_Open</attribute>
          <attribute name='action'>example.open</attribute>
        </item>
      </section>
      <section>
        <item>
          <attribute name='label' translatable='yes'>Rain</attribute>
          <attribute name='action'>example.rain</attribute>
        </item>
      </section>
      <section>
        <item>
          <attribute name='label' translatable='yes'>_Quit</attribute>
          <attribute name='action'>example.quit</attribute>
        </item>
      </section>
    </submenu>
    <submenu>
      <attribute name='label' translatable='yes'>_Edit</attribute>
      <item>
        <attribute name='label' translatable='yes'>_Cut</attribute>
        <attribute name='action'>example.cut</attribute>
      </item>
      <item>
        <attribute name='label' translatable='yes'>_Copy</attribute>
        <attribute name='action'>example.copy</attribute>
      </item>
      <item>
        <attribute name='label' translatable='yes'>_Paste</attribute>
        <attribute name='action'>example.paste</attribute>
      </item>
    </submenu>
  </menu>
</interface>"

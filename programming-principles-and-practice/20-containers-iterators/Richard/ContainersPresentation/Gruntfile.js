module.exports = function (grunt) {

    // Project configuration.
    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        concat: {
            options: {
                separator: ';',
            },
            dist: {
                src: ['app/bower_components/highlightjs/highlight.pack.js',
                    'app/bower_components/reveal.js/lib/js/head.min.js',
                    'app/bower_components/reveal.js/js/reveal.js'],
                dest: 'app/build/<%= pkg.name %>.js',
            },
        },
        uglify: {
            options: {
                banner: '/*! <%= pkg.name %> <%= grunt.template.today("yyyy-mm-dd") %> */\n'
            },
            build: {
                src: 'app/build/<%= pkg.name %>.js',
                dest: 'app/build/<%= pkg.name %>.min.js'
            }
        }
    });
    
    // Load the plugin that provides the "uglify" task.
    grunt.loadNpmTasks('grunt-contrib-uglify');
    grunt.loadNpmTasks('grunt-contrib-concat');

    // Default task(s).
    grunt.registerTask('default', ['concat', 'uglify']);

};